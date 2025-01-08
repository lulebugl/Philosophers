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

void free_data(t_data *data)
{
	int i;
	
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(data->philo);
	memset(data, 0, sizeof(t_data));
}

int	create_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		memset(&data->philo[i], 0, sizeof(t_philo));
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		if (i % 2)
			usleep(data->time_to_eat / 2);
		data->philo[i].last_meal = get_time();
		if (pthread_create(&data->philo[i].th, NULL, &routine,
			(void *)&data->philo[i]))
			return (free_data(data), 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 7)
		return (usage(), 0);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (create_philos(&data))
		return (1);

	int i = -1;
	while (++i < data.nb_philo)
		pthread_join(data.philo[i].th, NULL);
	free_data(&data);
	// if (launch_routines(&data) != 0)
	// 	return (1);
	return (0);
}
