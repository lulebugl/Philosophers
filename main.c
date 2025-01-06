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

static void	usage(void)
{
	printf("usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 4)
	{
		parse_params(&data, argc, argv);
		if (launch_routines(&data) != 0)
			return (clean_memory(&data), 1);
		return (0);
	}
	usage();
	return (0);
}

