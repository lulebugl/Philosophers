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

// bool	is_full(t_philo *ph)
// {
// 	bool	res;

// 	res = false;
// 	pthread_mutex_lock(&ph->meal_lock);
// 	if (ph->full == 1)
// 		res = true;
// 	pthread_mutex_unlock(&ph->meal_lock);
// 	return (res);
// }

bool	stop_dinner(t_dinner *dinner)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&dinner->death_mutex);
	if (dinner->stop == 1)
		res = true;
	pthread_mutex_unlock(&dinner->death_mutex);
	return (res);
}

void	routine_msg(char *msg, t_philo *ph)
{
	pthread_mutex_lock(&ph->dinner->print);
	if (stop_dinner(ph->dinner) || DEBUG == true)
	{
		pthread_mutex_unlock(&ph->dinner->print);	
		return ;
	}
	if (msg)
		printf("%s%ld%s %d %s", CYAN, get_time() - ph->dinner->start, RESET,
			ph->id, msg);
	pthread_mutex_unlock(&ph->dinner->print);
}

void	incremental_sleep(t_dinner *dinner, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		if (stop_dinner(dinner))
			break ;
		usleep(100);
	}
}

static void	*poor_philo(t_dinner *dinner)
{
	routine_msg(FORK, dinner->philo);
	usleep(dinner->time_to_die * 1000);
	routine_msg(DIED, dinner->philo);
	return (NULL);
}

static void	start_routine(t_philo *ph)
{
	t_dinner	*dinner;

	dinner = ph->dinner;
	pthread_mutex_lock(ph->left_fork);
	routine_msg(FORK, ph);
	pthread_mutex_lock(ph->right_fork);
	routine_msg(FORK, ph);
	routine_msg(EATING, ph);
	pthread_mutex_unlock(&ph->meal_lock);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->meal_lock);
	incremental_sleep(dinner, dinner->time_to_eat);
	if (stop_dinner(dinner) == false)
	{
		pthread_mutex_lock(&ph->meal_lock);
		ph->times_eaten++;
		pthread_mutex_unlock(&ph->meal_lock);
	}
	routine_msg(SLEEPING, ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	incremental_sleep(dinner, dinner->time_to_sleep);
	routine_msg(THINKING, ph);
}

void	*routine(void *arg)
{
	t_philo	*ph;
	t_dinner	*dinner;

	ph = (t_philo *)arg;
	dinner = ph->dinner;
	if (dinner->nb_philo == 1)
		return (poor_philo(dinner));
	while (stop_dinner(dinner) == false)
	{
		start_routine(ph);
	}
	return (NULL);
}

