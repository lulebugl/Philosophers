/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:32:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/06 15:32:45 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_msg(char *msg, t_philo *ph)
{
	if (DEBUG == true)
		return ;
	pthread_mutex_lock(&ph->data->print);
	if (msg)
		printf("%s%ld%s %d %s", CYAN, get_time() - ph->data->start, RESET,
			ph->id, msg);
	pthread_mutex_unlock(&ph->data->print);
}

void	incremental_sleep(t_data *data, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		if (data->dead == 1)
			break ;
		usleep(100);
	}
}

static void *poor_philo(t_data *data)
{
	routine_msg(FORK, data->philo);
	usleep(data->time_to_die * 1000);
	routine_msg(DIED, data->philo);
	return (NULL);
}

static void start_routine(t_philo *ph)
{
	t_data *data;
	
	data = ph->data;
	pthread_mutex_lock(ph->left_fork);
	routine_msg(FORK, ph);
	pthread_mutex_lock(ph->right_fork);
	routine_msg(FORK, ph);
	routine_msg(EATING, ph);
	ph->last_meal = get_time();
	incremental_sleep(data, data->time_to_eat);
	ph->times_eaten++;
	routine_msg(SLEEPING, ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	incremental_sleep(data, data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)arg;
	data = ph->data;
	if (data->nb_philo == 1)
		return (poor_philo(data));
	while (data->dead != 1)
	{
		start_routine(ph);
	}
	return (NULL);
}

void	*routine2(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (ph->data->dead == 0)
	{
		// should it complete the routine before returning ?
		// should it be the last message seen?
		if (get_time() - ph->last_meal > ph->data->time_to_die)
		{
			ph->data->dead = 1;
			routine_msg(DIED, ph);
			return (NULL);
		}
		pthread_mutex_lock(ph->left_fork);
		routine_msg(FORK, ph);
		pthread_mutex_lock(ph->right_fork);
		routine_msg(FORK, ph);
		routine_msg(EATING, ph);
		// usleep(ph->data->time_to_eat * 1000);
		incremental_sleep(ph->data, ph->data->time_to_eat * 1000);
		// if (should_routine_continue(ph))
		// {
		// 	ph->times_eaten++;
		// 	ph->last_meal = get_time();
		// }
		// else
		// {
		// 	return (NULL);
		// }
		routine_msg("is sleeping\n", ph);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		usleep(ph->data->time_to_sleep * 1000);
		incremental_sleep(ph->data, ph->data->time_to_sleep * 1000);
		routine_msg(THINKING, ph);
		// usleep(ph->data->time_to_sleep * 1000);
		// incremental_sleep(ph->data, ph->data->time_to_sleep * 1000);
	}
	return (NULL);
}

