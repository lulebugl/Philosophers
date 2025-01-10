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
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG false
# endif

# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

# define MAX_PHILOS 250


# define MSG_DIED       "died\n"
# define MSG_FORK       "has taken a fork\n"
# define MSG_EATING     "is eating\n"
# define MSG_THINKING   "is thinking\n"
# define MSG_SLEEPING   "is sleeping\n"

# define ERR_MUST_EAT \
	"<number of times each philosopher must eat> must be a positive integer \
between 1 and 2147483647.\n"

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	pthread_t			th;
	int					id;
	unsigned int		times_eaten;
	time_t				last_meal;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_sim				*sim;
}						t_philo;

typedef struct s_sim
{
	unsigned int		nb_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					must_eat;
	time_t				start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_lock;
	bool				should_stop;
	t_philo				*philo;
}						t_sim;

int						init_dinner(t_dinner *dinner, int argc, char **argv);

time_t					get_time(void);
int						create_supervisor(t_dinner *dinner);
void					wait_for_everyone(t_dinner *dinner);
void					clean(t_dinner *dinner);
int						simple_atoi(const char *str);
size_t					ft_strlen(const char *s);
int						contains_only_digits(char *str);
int						msg(const char *msg);
void					routine_msg(char *msg, t_philo *ph);

int						clean_memory(t_dinner *dinner);

void					*routine(void *philo);
int						launch_routines(t_dinner *dinner);
time_t					elapsed_time(time_t start);
#endif

