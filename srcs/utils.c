/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:27:46 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/10 17:27:54 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	stop_sim(t_sim *sim)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&sim->stop_mutex);
	if (sim->should_stop == true)
		status = true;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (status);
}

void	wait_for_everyone(time_t start)
{
	while (get_time_in_ms() < start)
		continue ;
}

void	incremental_sleep(t_sim *sim, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (stop_sim(sim))
			break ;
		usleep(100);
	}
}

void	clean(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philo[i].meal_lock);
	}
	free(sim->forks);
	free(sim->philo);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	memset(sim, 0, sizeof(t_sim));
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
