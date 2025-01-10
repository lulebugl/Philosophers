/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:33 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/10 18:20:36 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void debug_philo_config(t_sim *sim, int i)
{
	printf("\n\033[0;36m=== Philosopher %d Configuration ===\033[0m\n", i
		+ 1);
	printf("Position: %d\n", i);
	printf("Thread ID: %lu\n", sim->philo[i].th);
	printf("Philosopher ID: %d\n", sim->philo[i].id);
	printf("Left fork: %p (index: %d)\n", (void *)sim->philo[i].left_fork,
		i);
	printf("Right fork: %p (index: %d)\n", (void *)sim->philo[i].right_fork,
		(i + 1) % sim->nb_philo);
	printf("Times eaten: %u\n", sim->philo[i].times_eaten);
	printf("Last meal time: %ld\n", sim->philo[i].last_meal);
	printf("Simulation parameters:\n");
	printf("  Time to die: %u\n", sim->time_to_die);
	printf("  Time to eat: %u\n", sim->time_to_eat);
	printf("  Time to sleep: %u\n", sim->time_to_sleep);
	printf("============================\n\n");
}