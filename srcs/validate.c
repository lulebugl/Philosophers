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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

static int	validate_param(unsigned int *sim, char *param, char *param_name)
{
	int	n;

	n = parse_param(param);
	if (n <= 0)
	{
		printf("%s must be a positive integer between 1 and 2147483647.\n",
			param_name);
		return (0);
	}
	*sim = (unsigned int)n;
	return (1);
}

int	validate_params(t_sim *sim, int argc, char **argv)
{
	sim->must_eat = -1;
	sim->nb_philo = parse_param(argv[1]);
	if (sim->nb_philo < 1 || sim->nb_philo > MAX_PHILOS)
	{
		printf("There must be between 1 and %d philosophers.\n", MAX_PHILOS);
		return (1);
	}
	if (!validate_param(&sim->time_to_die, argv[2], "<time to die>"))
		return (1);
	if (!validate_param(&sim->time_to_eat, argv[3], "<time to eat>"))
		return (1);
	if (!validate_param(&sim->time_to_sleep, argv[4], "<time to sleep>"))
		return (1);
	if (argc == 6)
	{
		sim->must_eat = parse_param(argv[5]);
		if (sim->must_eat < 0)
		{
			printf(ERR_MUST_EAT);
			return (1);
		}
	}
	return (0);
}
