/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:32:28 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/06 15:32:30 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philo)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		pthread_mutex_destroy(&dinner->philo[i].meal_lock);
	}
	free(dinner->forks);
	free(dinner->philo);
	pthread_mutex_destroy(&dinner->print);
	pthread_mutex_destroy(&dinner->stop_lock);
	memset(dinner, 0, sizeof(t_dinner));
}

int	clean_memory(t_dinner *dinner)
{
	int i;

	i = 0;
	while (i < dinner->nb_philo)
	{
		if (dinner->philo)
		{
			free(dinner->philo);
		}
		i--;
	}
	memset(dinner, 0, sizeof(t_dinner));
	return (0);
}
