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

static int init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->nb_philo = (unsigned int)ft_atol(argv[1]);
	if (data->nb_philo < 1)
		return (-1);
	if (data->)
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
