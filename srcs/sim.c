/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:22:22 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/10 17:22:32 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** to avoid circular lock ordering
** Even numbered philosophers take right fork first
** Odd numbered philosophers take left fork first
*/
static void	init_philo(t_sim *sim, t_philo *philo, int pos)
{
	memset(philo, 0, sizeof(t_philo));
	philo->id = pos + 1;
	philo->sim = sim;
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &sim->forks[pos];
		philo->left_fork = &sim->forks[(pos + 1) % sim->nb_philo];
	}
	else
	{
		philo->left_fork = &sim->forks[pos];
		philo->right_fork = &sim->forks[(pos + 1) % sim->nb_philo];
	}
	pthread_mutex_init(&sim->philo[pos].meal_lock, NULL);
}

int	init_sim(t_sim *sim, int argc, char **argv)
{
	int	i;

	i = 0;
	memset(sim, 0, sizeof(t_sim));
	if (validate_params(sim, argc, argv) != 0)
		return (1);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philo);
	if (!sim->forks)
		return (1);
	sim->philo = malloc(sizeof(t_philo) * sim->nb_philo);
	if (!sim->philo)
		return (free(sim->forks), 1);
	while (i < sim->nb_philo)
		pthread_mutex_init(&sim->forks[i++], NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->stop_mutex, NULL);
	sim->should_stop = false;
	sim->start = get_time_in_ms() + (sim->nb_philo * PHILO_MS_INIT_TIME);
	return (0);
}

int	start_sim(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philo)
	{
		init_philo(sim, &sim->philo[i], i);
		if (sim->must_eat == 0)
			return (0);
		if (pthread_create(&sim->philo[i].th, NULL, &philo,
				(void *)&sim->philo[i]) != 0)
			return (clean(sim), 1);
	}
	if (sim->nb_philo > 1)
		if (pthread_create(&sim->supervisor, NULL, &supervisor,
				(void *)sim) != 0)
			return (clean(sim), 1);
	return (0);
}
