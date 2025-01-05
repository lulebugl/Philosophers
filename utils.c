/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:02:01 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/03 20:03:51 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int msg(const char *msg)
{
	printf(msg, MAX_PHILOS);
	return (-1);
}

int	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	simple_atoi(const char *str)
{
	unsigned long long	res;
	int			i;

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
			return (0);
	}
	if (res > INT_MAX)
		return (0);
	return ((int)res);
}

