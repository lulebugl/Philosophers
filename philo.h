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

typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
}					t_data;

int	simple_atoi(const char *str);
size_t				ft_strlen(const char *s);
int					contains_only_digits(char *str);
int					msg(const char *msg);

#endif

