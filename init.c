/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:22:27 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/06 20:06:11 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

static int	parse_param(const char *str)
{
	unsigned long long	res;
	int					i;

	i = 0;
	res = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + str[i] - 48;
			i++;
		}
		else
			return (-1);
	}
	if (res > INT_MAX)
		return (-1);
	return ((int)res);
}

static int	validate_param(unsigned int *dinner, char *param, char *param_name)
{
	*dinner = parse_param(param);
	if (dinner <= 0)
	{
		printf("%s must be a positive integer between 1 and 2147483647.\n",
			param);
		return (0);
	}
	return (1);
}

static int validate_params(t_dinner *dinner , int argc, char **argv)
{
	dinner->must_eat = -1;
	dinner->nb_philo = parse_param(argv[1]);
	if (dinner->nb_philo < 1 || dinner->nb_philo > MAX_PHILOS)
	{
		printf("There must be between 1 and %d philosophers.\n", MAX_PHILOS);
		return (1);
	}
	if (!validate_param(&dinner->time_to_die, argv[2], "<time to die>"))
		return (1);
	if (!validate_param(&dinner->time_to_eat, argv[3], "<time to eat>"))
		return (1);
	if (!validate_param(&dinner->time_to_sleep, argv[4], "<time to sleep>"))
		return (1);
	if (argc == 6)
	{
		dinner->must_eat = parse_param(argv[5]);
		if (dinner->must_eat < 0)
		{
			printf(INV_MUST_EAT);
			return (1);
		}
	}
	return (0);
}

int	init_dinner(t_dinner *dinner, int argc, char **argv)
{
	int i;

	i = -1;
	memset(dinner, 0, sizeof(t_dinner));
	if (validate_params(dinner, argc, argv) != 0)
		return (1);
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->nb_philo);
	if (!dinner->forks)
		return (1);
	dinner->philo = malloc(sizeof(t_philo) * dinner->nb_philo);
	if (!dinner->philo)
		return (free(dinner->forks), 1);
	while (++i < dinner->nb_philo)
		pthread_mutex_init(&dinner->forks[i], NULL);
	pthread_mutex_init(&dinner->print, NULL);
	pthread_mutex_init(&dinner->death_mutex, NULL);
	dinner->start = get_time();
	return (0);
}
