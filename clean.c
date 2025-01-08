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

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philo);
	memset(data, 0, sizeof(t_data));
}

int	clean_memory(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo)
		{
			free(data->philo);
		}
		i--;
	}
	memset(data, 0, sizeof(t_data));
	return (0);
}
