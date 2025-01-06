/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:04:22 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/06 20:04:33 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// static int	parse_param(const char *str)
// {
// 	unsigned long long	res;
// 	int					i;

// 	i = 0;
// 	res = 0;
// 	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' ') && str[i])
// 		i++;
// 	if (str[i] == '+')
// 		i++;
// 	while (str[i])
// 	{
// 		if (str[i] >= '0' && str[i] <= '9')
// 		{
// 			res = res * 10 + str[i] - 48;
// 			i++;
// 		}
// 		else
// 			return (-1);
// 	}
// 	if (res > INT_MAX)
// 		return (-1);
// 	return ((int)res);
// }

// static int	validate_param(unsigned int *data, char *param, char *param_name)
// {
// 	*data = parse_param(param);
// 	if (data <= 0)
// 	{
// 		printf("%s must be a positive integer between 1 and 2147483647.\n",
// 			param);
// 		return (0);
// 	}
// 	return (1);
// }

// int	init_data(t_data *data, int argc, char **argv)
// {
// 	memset(data, 0, sizeof(t_data));
// 	data->must_eat = -1;
// 	data->nb_philo = parse_param(argv[1]);
// 	if (data->nb_philo < 1 || data->nb_philo > MAX_PHILOS)
// 	{
// 		printf("There must be between 1 and %d philosophers.\n", MAX_PHILO);
// 		return (1);
// 	}
// 	if (!validate_param(&data->time_to_die, argv[2], "<time to die>"))
// 		return (1);
// 	if (!validate_param(&data->time_to_eat, argv[3], "<time to eat>"))
// 		return (1);
// 	if (!validate_param(&data->time_to_sleep, argv[4], "<time to sleep>"))
// 		return (1);
// 	if (argc >= 6)
// 	{
// 		data->must_eat = parse_param(argv[5]);
// 		if (data->must_eat < 0)
// 		{
// 			printf(INV_MUST_EAT);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
