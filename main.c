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

int	start_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philo)
	{
		memset(&dinner->philo[i], 0, sizeof(t_philo));
		dinner->philo[i].id = i + 1;
		dinner->philo[i].dinner = dinner;
		pthread_mutex_init(&dinner->philo[i].meal_lock, NULL);
		dinner->philo[i].left_fork = &dinner->forks[i];
		dinner->philo[i].right_fork = &dinner->forks[(i + 1) % dinner->nb_philo];
		// pthread_mutex_lock(&dinner->philo[i].meal_lock);
		// dinner->philo[i].last_meal = dinner->start;
		// pthread_mutex_unlock(&dinner->philo[i].meal_lock);
		// if (i % 2)
		// 	usleep(dinner->time_to_eat / 2);
		if (pthread_create(&dinner->philo[i].th, NULL, &routine,
				(void *)&dinner->philo[i]) != 0)
			return (clean(dinner), 1);
	}
	if (dinner->nb_philo > 1)
		if (create_supervisor(dinner) != 0)
			return (clean(dinner), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	int		i;

	if (argc < 5 || argc > 6)
		return (usage(), 0);
	if (init_dinner(&dinner, argc, argv) != 0)
		return (1);
	if (start_dinner(&dinner))
		return (1);
	i = -1;
	while (++i < dinner.nb_philo)
		pthread_join(dinner.philo[i].th, NULL);
	clean(&dinner);
	return (0);
}

