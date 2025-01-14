/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:40:50 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/10 17:40:56 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine_msg(char *msg, t_philo *ph)
{
	time_t	timestamp;

	timestamp = get_time_in_ms() - ph->sim->start;
	pthread_mutex_lock(&ph->sim->print_mutex);
	if (stop_sim(ph->sim) || DEBUG == true)
	{
		pthread_mutex_unlock(&ph->sim->print_mutex);
		return ;
	}
	if (COLOR == true)
		printf("%s%ld%s %d %s", CYAN, timestamp, RESET, ph->id, msg);
	else
		printf("%ld %d %s", timestamp, ph->id, msg);
	pthread_mutex_unlock(&ph->sim->print_mutex);
}

static void	*poor_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	routine_msg(MSG_FORK, philo);
	incremental_sleep(philo->sim, philo->sim->time_to_die);
	routine_msg(MSG_DIED, philo);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	think(t_philo *philo)
{
	time_t	time_to_think;
	time_t	time_left;

	pthread_mutex_lock(&philo->meal_lock);
	time_left = philo->sim->time_to_die - (get_time_in_ms() - philo->last_meal);
	time_to_think = (time_left - philo->sim->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > philo->sim->time_to_eat)
		time_to_think = philo->sim->time_to_eat / 2;
	routine_msg(MSG_THINKING, philo);
	incremental_sleep(philo->sim, time_to_think);
}

static void	start_routine(t_philo *ph)
{
	t_sim	*sim;

	sim = ph->sim;
	pthread_mutex_lock(ph->left_fork);
	routine_msg(MSG_FORK, ph);
	pthread_mutex_lock(ph->right_fork);
	routine_msg(MSG_FORK, ph);
	routine_msg(MSG_EATING, ph);
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&ph->meal_lock);
	incremental_sleep(sim, sim->time_to_eat);
	if (stop_sim(sim) == false)
	{
		pthread_mutex_lock(&ph->meal_lock);
		ph->times_eaten++;
		pthread_mutex_unlock(&ph->meal_lock);
	}
	routine_msg(MSG_SLEEPING, ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	incremental_sleep(sim, sim->time_to_sleep);
	think(ph);
}

void	*philo(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = sim->start;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_for_everyone(sim->start);
	if (sim->nb_philo == 1)
		return (poor_philo(philo));
	if (philo->id % 2)
		incremental_sleep(sim, (sim->time_to_eat / 2));
	while (stop_sim(sim) == false)
		start_routine(philo);
	return (NULL);
}
