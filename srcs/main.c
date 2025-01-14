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
<time_to_eat> <time_to_sleep> \
optional:<number_of_times_each_philosopher_must_eat>\n");
}

int	main(int argc, char **argv)
{
	t_sim	sim;
	int		i;

	if (argc < 5 || argc > 6)
		return (usage(), 0);
	if (init_sim(&sim, argc, argv) != 0)
		return (1);
	if (start_sim(&sim))
		return (1);
	i = 0;
	while (++i < sim.nb_philo)
		pthread_join(sim.philo[i++].th, NULL);
	if (sim.nb_philo > 1)
		pthread_join(sim.supervisor, NULL);
	clean(&sim);
	return (0);
}
