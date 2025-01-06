/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:22:27 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/06 19:22:28 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int validate_param(unsigned int *value, char *arg, char *key)
{
	*value = simple_atoi(arg);
	if (value <= 0)
	{
		printf("%s must be a positive integer between 1 and 2147483647.\n",
			key);
		return (1);
	}
	return (0);
}

int	parse_params(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	memset(data, 0, sizeof(t_data));
	data->must_eat = -1;
	data->nb_philo = simple_atoi(argv[1]);
	if (data->nb_philo <= 0 || data->nb_philo > MAX_PHILOS)
		return (msg(INVALID_PHILO_INPUT));
	if (validate_param(&data->time_to_die, argv[2], "<time to die>"))
		return (1);
	if (validate_param(&data->time_to_eat, argv[3], "<time to eat>"))
		return (1);
	if (validate_param(&data->time_to_sleep, argv[4], "<time to sleep>"))
		return (1);
	// data->time_to_die = simple_atoi(argv[2]);
	// if (data->time_to_die <= 0)
	// 	return (msg("<time to die> must be a positive integer between 1 and 2147483647.\n"));
	// data->time_to_eat = simple_atoi(argv[3]);
	// if (data->time_to_eat <= 0)
	// 	return (msg("<time to eat> must be a positive integer between 1 and 2147483647.\n"));
	// data->time_to_sleep = simple_atoi(argv[4]);
	// if (data->time_to_sleep <= 0)
	// 	return (msg("<time to sleep> must be a positive integer between 1 and 2147483647.\n"));
	if (argc >= 6)
	{
		data->must_eat = simple_atoi(argv[5]);
		if (data->must_eat < 0)	
			return (msg(INV_MUST_EAT));
	}
	return (0);
}