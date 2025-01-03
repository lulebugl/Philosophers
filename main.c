/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:58:56 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/03 16:58:57 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
}

static int	parse_arg(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	memset(data, 0, sizeof(t_data));
	while (++i < argc)
		if (!contains_only_digits(argv[i]))
			return (msg("Parameters can only be positive numbers.\n"));
	data->nb_philo = simple_atoi(argv[1]);
	if (data->nb_philo <= 0 || data->nb_philo > MAX_PHILOS)
		return (msg(INVALID_PHILO_INPUT));
	data->time_to_die = simple_atoi(argv[2]);
	if (data->time_to_die <= 0)
		return (msg("time to die must be a positive integer between 1 and 2147483647.\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 4)
	{
		parse_arg(&data, argc, argv);
		return (0);
	}
	usage();
	return (0);
}
