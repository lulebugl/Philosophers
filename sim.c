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

void	init_philo(t_sim *sim, t_philo *philo, int pos)
{
	memset(philo, 0, sizeof(t_philo));
	philo->id = pos + 1;
	philo->sim = sim;
	philo->left_fork = &sim->forks[pos];
	philo->right_fork = &sim->forks[(pos + 1) % sim->nb_philo];
	pthread_mutex_init(&sim->philo[pos].meal_lock, NULL);
}

int	start_sim(t_sim *sim)
{
	int			i;
	pthread_t	sp;

	i = -1;
	while (++i < sim->nb_philo)
	{
		init_philo(sim, &sim->philo[i], i);
		if (sim->must_eat == 0)
			return (0);
		/* Debug output */
		debug_philo_config(sim, i);

		if (i % 2)
			usleep(sim->time_to_eat / 2);
		if (pthread_create(&sim->philo[i].th, NULL, &philo,
				(void *)&sim->philo[i]) != 0)
			return (clean(sim), 1);
	}
	if (sim->nb_philo > 1)
		if (pthread_create(&sp, NULL, &supervisor, (void *)sim) != 0)
			return (clean(sim), 1);
	return (0);
}

