/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:28:05 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/08 16:28:11 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	someone_died(t_philo *ph)
{
	time_t last_meal;
	
	last_meal = get_time() - ph->last_meal;
	// printf("%s%ld%s %d %s", RED, last_meal, RESET,
	// 	ph->id, "last meal\n");
	if (last_meal >= ph->dinner->time_to_die)
	{
		pthread_mutex_lock(&ph->dinner->stop_lock);
		ph->dinner->stop = true;
		pthread_mutex_unlock(&ph->dinner->stop_lock);
		pthread_mutex_lock(&ph->dinner->print);
		printf("%s%ld%s %d %s", RED, get_time() - ph->dinner->start, RESET,
			ph->id, DIED);
		pthread_mutex_unlock(&ph->dinner->print);
		pthread_mutex_unlock(&ph->meal_lock);
		return (true);
	}
	return (false);
}

bool	should_stop_dinner(t_dinner *dinner)
{
	int		i;
	bool	finished_eating;
	t_philo	*ph;

	i = -1;
	ph = dinner->philo;
	finished_eating = true;
	wait_for_everyone(dinner);
	while (++i < dinner->nb_philo)
	{
		pthread_mutex_lock(&ph[i].meal_lock);
		if (someone_died(&ph[i]))
			return (true);
		if (dinner->must_eat != -1 && ph[i].times_eaten < dinner->must_eat)
			finished_eating = false;
		pthread_mutex_unlock(&ph[i].meal_lock);
	}
	if (dinner->must_eat != -1 && finished_eating)
	{
		pthread_mutex_lock(&dinner->stop_lock);
		dinner->stop = true;
		pthread_mutex_unlock(&dinner->stop_lock);
		return (true);
	}
	return (false);
}

static void	*supervise(void *arg)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)arg;
	if (dinner->must_eat == 0)
		return (NULL);
	while (1)
	{
		if (should_stop_dinner(dinner))
		{
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

int	create_supervisor(t_dinner *dinner)
{
	pthread_t	sp;

	if (pthread_create(&sp, NULL, &supervise, (void *)dinner) != 0)
		return (1);
	return (0);
}

