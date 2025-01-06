/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:32:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/06 15:32:45 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->print);
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	i = -1;
	while (++i < data->nb_philo)
		memset(&data->philo[i], 0, sizeof(t_philo));
	free(data);
}

static void	routine_msg(char *msg, t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print);
	if (msg)
		printf("%s%ld%s %d %s", CYAN, get_time() - ph->data->start, RESET,
			ph->id, msg);
	pthread_mutex_unlock(&ph->data->print);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	routine_msg("has taken a fork\n", ph);
	pthread_mutex_lock(ph->right_fork);
	routine_msg("has taken a fork\n", ph);
	routine_msg("is eating\n", ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	ph->times_eaten++;
}

// void	philo_sleep(t_table *table, time_t sleep_time)
// {
// 	time_t	wake_up;

// 	wake_up = get_time() + sleep_time;
// 	while (get_time() < wake_up)
// 	{
// 		if (has_simulation_stopped(table))
// 			break ;
// 		usleep(100);
// 	}
// }

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (ph->data->dead == 0)
	{
		// should it complete the routine before returning ?
		if (ph->data->must_eat == ph->times_eaten)
			return (NULL);
		// should it be the last message seen?
		if (get_time() - ph->last_meal > ph->data->time_to_die)
		{
			ph->data->dead = 1;
			routine_msg("died\n", ph);
			return (NULL);
		}
		pthread_mutex_lock(ph->left_fork);
		routine_msg("has taken a fork\n", ph);
		pthread_mutex_lock(ph->right_fork);
		routine_msg("has taken a fork\n", ph);
		routine_msg("is eating\n", ph);
		usleep(ph->data->time_to_eat * 1000);
		ph->times_eaten++;
		ph->last_meal = get_time();
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		routine_msg("is sleeping\n", ph);
		usleep(ph->data->time_to_sleep * 1000);
		routine_msg("is thinking\n", ph);
		usleep(ph->data->time_to_sleep * 1000);
	}
	return (NULL);
}

int	init_philo(t_data *data)
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
		pthread_create(&data->philo[i].th, NULL, &routine,
			(void *)&data->philo[i]);
	}
	return (0);
}

int	launch_routines(t_data *data)
{
	int	i;

	i = -1;
	// data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	// if (!data->forks)
	// 	return (1);
	// data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	// if (!data->philo)
	// {
	// 	free(data->forks);
	// 	return (1);
	// }
	// while (++i < data->nb_philo)
	// 	pthread_mutex_init(&data->forks[i], NULL);
	// pthread_mutex_init(&data->print, NULL);
	// // pthread_mutex_init(data->death_mutex, NULL);
	// data->start = get_time();
	init_philo(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].th, NULL);
	// destroy_all(data);
	return (0);
}

