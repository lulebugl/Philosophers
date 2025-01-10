/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:28:05 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/08 16:28:11 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static bool	someone_died(t_philo *ph)
// {
// 	time_t last_meal;
	
// 	last_meal = get_time() - ph->last_meal;
// 	// printf("%s%ld%s %d %s", RED, last_meal, RESET,
// 	// 	ph->id, "last meal\n");
// 	if (last_meal >= ph->sim->time_to_die)
// 	{
// 		pthread_mutex_lock(&ph->sim->stop_lock);
// 		ph->sim->stop = true;
// 		pthread_mutex_unlock(&ph->sim->stop_lock);
// 		pthread_mutex_lock(&ph->sim->print);
// 		printf("%s%ld%s %d %s", RED, get_time() - ph->sim->start, RESET,
// 			ph->id, DIED);
// 		pthread_mutex_unlock(&ph->sim->print);
// 		pthread_mutex_unlock(&ph->meal_lock);
// 		return (true);
// 	}
// 	return (false);
// }

// bool	should_stop_sim(t_sim *sim)
// {
// 	int		i;
// 	bool	finished_eating;
// 	t_philo	*ph;

// 	i = -1;
// 	ph = sim->philo;
// 	finished_eating = true;
// 	wait_for_everyone(sim);
// 	while (++i < sim->nb_philo)
// 	{
// 		pthread_mutex_lock(&ph[i].meal_lock);
// 		if (someone_died(&ph[i]))
// 			return (true);
// 		if (sim->must_eat != -1 && ph[i].times_eaten < sim->must_eat)
// 			finished_eating = false;
// 		pthread_mutex_unlock(&ph[i].meal_lock);
// 	}
// 	if (sim->must_eat != -1 && finished_eating)
// 	{
// 		pthread_mutex_lock(&sim->stop_lock);
// 		sim->stop = true;
// 		pthread_mutex_unlock(&sim->stop_lock);
// 		return (true);
// 	}
// 	return (false);
// }

void	*supervisor(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	if (sim->must_eat == 0)
		return (NULL);
	while (1)
	{
		// if (should_stop_sim(sim))
		// {
		// 	return (NULL);
		// }
		usleep(500);
	}
	return (NULL);
}

