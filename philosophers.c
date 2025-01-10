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

// void init_philo(t_sim *sim, t_philo *philo, int pos)
// {
// 	memset(philo, 0, sizeof(t_philo));
// 	philo->id = pos + 1;
// 	philo->left_fork = &sim->forks[pos];
// 	philo->right_fork = &sim->forks[(pos + 1) % sim->nb_philo];
// 	pthread_mutex_init(&sim->philo[pos].meal_lock, NULL);
// }

static void	*poor_philo(t_sim *sim)
{
	routine_msg(MSG_FORK, sim->philo);
	usleep(sim->time_to_die * 1000);
	routine_msg(MSG_DIED, sim->philo);
	return (NULL);
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
	routine_msg(MSG_THINKING, ph);
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
	wait_for_everyone(sim);
	if (philo->id % 2)
		usleep(200);
	if (sim->nb_philo == 1)
		return (poor_philo(sim));
	while (stop_sim(sim) == false)
	{
		start_routine(philo);
	}
	return (NULL);
}
