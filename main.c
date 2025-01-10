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


int	init_sim(t_sim *sim, int argc, char **argv)
{
	int i;

	i = -1;
	memset(sim, 0, sizeof(t_sim));
	if (validate_params(sim, argc, argv) != 0)
		return (1);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philo);
	if (!sim->forks)
		return (1);
	sim->philo = malloc(sizeof(t_philo) * sim->nb_philo);
	if (!sim->philo)
		return (free(sim->forks), 1);
	while (++i < sim->nb_philo)
		pthread_mutex_init(&sim->forks[i], NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->stop_mutex, NULL);
	sim->should_stop = false;
	sim->start = get_time_in_ms() + (sim->nb_philo * 2);
	return (0);
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
	i = -1;
	while (++i < sim.nb_philo)
		pthread_join(sim.philo[i].th, NULL);
	clean(&sim);
	return (0);
}

