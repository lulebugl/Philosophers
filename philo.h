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
# include <sys/time.h>
# include <unistd.h>

/** Macros **/
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define RESET	"\033[0m"

# define MAX_PHILOS 250
# define INV_MUST_EAT \
	"<number of times each philosopher must eat> must be a positive integer \
between 1 and 2147483647.\n"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			th;
	int					id;
	unsigned int		times_eaten;
	time_t				last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	time_t				start;
	unsigned int		nb_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		must_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	// pthread_mutex_t	*death_mutex; why?
	int					dead;
	t_philo				*philo;
}						t_data;

int		init_data(t_data *data, int argc, char **argv);

time_t					get_time(void);
int						simple_atoi(const char *str);
size_t					ft_strlen(const char *s);
int						contains_only_digits(char *str);
int						msg(const char *msg);
int						clean_memory(t_data *data);

int						launch_routines(t_data *data);
time_t elapsed_time(time_t start);
#endif

