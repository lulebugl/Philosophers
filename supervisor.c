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

static bool someone_died(t_philo *ph)
{
	// printf("%s%ld%s %d %s", CYAN, get_time() - ph->last_meal, RESET,
	// 	ph->id, "last meal");
	if (get_time() - ph->last_meal >= ph->data->time_to_die)
	{
		ph->data->dead = 1;
		// routine_msg(DIED, ph);
			printf("%s%ld%s %d %s", RED, get_time() - ph->data->start, RESET,
				ph->id, DIED);
		return (true);
	}
	return (false);
}

bool	should_stop_dinner(t_data *data)
{
	int i;
	t_philo *ph;
	
	i = -1;
	ph = data->philo;
	while (++i < data->nb_philo)
	{
		if (someone_died(&ph[i]))
			return (true);
	}
	// if (data->dead == 1)
	// {
	// 	printf("someone died\n");
	// 	return (true);
	// }
	
	return (false);
}

static void	*supervise(void *arg)
{
	while (1)
	{
		//printf("supervising\n");
		if (should_stop_dinner((t_data *)arg) == true)
			return (NULL);
		usleep(10000);
	}
	return (NULL);
}

int	create_supervisor(t_data *data)
{
	pthread_t	sp;

	if (pthread_create(&sp, NULL, &supervise, (void *)data) != 0)
		return (1);
	return (0);
}