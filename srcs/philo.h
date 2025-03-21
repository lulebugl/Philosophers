/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:03:43 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/14 19:39:23 by llebugle         ###   ########.fr       */
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

# ifndef COLOR
#  define COLOR false
# endif

# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

# define MAX_PHILOS 200
# define PHILO_MS_INIT_TIME 15

# define MSG_DIED "died\n"
# define MSG_FORK "has taken a fork\n"
# define MSG_EATING "is eating\n"
# define MSG_THINKING "is thinking\n"
# define MSG_SLEEPING "is sleeping\n"

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
	int					nb_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					must_eat;
	time_t				start;
	pthread_t			supervisor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	bool				should_stop;
	t_philo				*philo;
}						t_sim;

int						validate_params(t_sim *sim, int argc, char **argv);
int						start_sim(t_sim *sim);
int						init_sim(t_sim *sim, int argc, char **argv);
void					*supervisor(void *arg);
void					*philo(void *arg);

/* utils */
size_t					ft_strlen(const char *s);
bool					stop_sim(t_sim *sim);
time_t					get_time_in_ms(void);
void					wait_for_everyone(time_t start);
void					clean(t_sim *sim);
void					incremental_sleep(t_sim *sim, time_t sleep_time);

/* debug */
void					debug_philo_config(t_sim *sim, int i);
void					debug_time_msg(t_philo *ph, const char *action,
							time_t wait_time);
void					debug_fork_msg(t_philo *ph, const char *fork_name,
							time_t wait_time);
void					start_routine_debug(t_philo *ph);

#endif
