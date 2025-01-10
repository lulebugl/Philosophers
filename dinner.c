
#include "philo.h"

bool	stop_sim(t_sim *sim)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&sim->stop_lock);
	if (sim->stop == true)
		res = true;
	pthread_mutex_unlock(&sim->stop_lock);
	return (res);
}

void	routine_msg(char *msg, t_philo *ph)
{
	pthread_mutex_lock(&ph->sim->print);
	if (stop_sim(ph->sim) || DEBUG == true)
	{
		pthread_mutex_unlock(&ph->sim->print);
		return ;
	}
	if (msg)
		printf("%s%ld%s %d %s", CYAN, get_time() - ph->sim->start, RESET,
			ph->id, msg);
	pthread_mutex_unlock(&ph->sim->print);
}

void	incremental_sleep(t_sim *sim, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		if (stop_sim(sim))
			break ;
		usleep(100);
	}
}

static void	*poor_philo(t_sim *sim)
{
	routine_msg(FORK, sim->philo);
	usleep(sim->time_to_die * 1000);
	routine_msg(DIED, sim->philo);
	return (NULL);
}

static void	start_routine(t_philo *ph)
{
	t_sim	*sim;

	sim = ph->sim;
	pthread_mutex_lock(ph->left_fork);
	routine_msg(FORK, ph);
	pthread_mutex_lock(ph->right_fork);
	routine_msg(FORK, ph);
	routine_msg(EATING, ph);
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->meal_lock);
	incremental_sleep(sim, sim->time_to_eat);
	if (stop_sim(sim) == false)
	{
		pthread_mutex_lock(&ph->meal_lock);
		ph->times_eaten++;
		pthread_mutex_unlock(&ph->meal_lock);
	}
	routine_msg(SLEEPING, ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	incremental_sleep(sim, sim->time_to_sleep);
	routine_msg(THINKING, ph);
}

void wait_for_everyone(t_sim *sim)
{
	while (get_time_in_ms() < sim->start)
		continue ;
}

void	*routine(void *arg)
{
	t_philo	*ph;
	t_sim	*sim;

	ph = (t_philo *)arg;
	sim = ph->sim;
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = sim->start;
	pthread_mutex_unlock(&ph->meal_lock);
	wait_for_everyone(sim);
	if (ph->id % 2)
		usleep(1);
	if (sim->nb_philo == 1)
		return (poor_philo(sim));
	while (stop_sim(sim) == false)
	{
		start_routine(ph);
	}
	return (NULL);
}

