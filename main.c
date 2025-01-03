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

static int msg(const char *msg)
{
	printf(msg, MAX_PHILOS);
	return (-1);
}

static int init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->nb_philo = (unsigned int)ft_atol(argv[1]);
	if (data->nb_philo < 1 || data->nb_philo > MAX_PHILOS)
		return (msg(INVALID_PHILO_INPUT));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;
	
	if (argc > 4)
	{
		init_data(&data, argv);
		return (0);
	}
	usage();
	return (0);
}
