/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:03:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/03 17:03:50 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/** Macros **/
# define MAX_PHILOS 250
# define INVALID_PHILO_INPUT \
	"usage : There must be between 1 and \
%d philosophers.\n"
# define INV_MUST_EAT \
	"<number of times each philosopher must eat> must be a positive integer \
between 1 and 2147483647.\n"

typedef struct s_philo
{
	pthread_t		th;
	unsigned int	id;
	unsigned int	times_eaten;
	uint64_t		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	// pthread_mutex_t	*death_mutex; why?
	int				dead;
	t_philo			*philo;
}					t_data;

int					simple_atoi(const char *str);
size_t				ft_strlen(const char *s);
int					contains_only_digits(char *str);
int					msg(const char *msg);

#endif

