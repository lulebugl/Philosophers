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
