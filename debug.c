/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:20:33 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/10 18:20:36 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_time_msg(t_philo *ph, const char *action, time_t wait_time)
{
	if (DEBUG == true)
	{
		pthread_mutex_lock(&ph->sim->print_mutex);
		if (COLOR)
			printf("%s[P%d] %s wait: %ldms%s\n", PURPLE, ph->id, action,
				wait_time, RESET);
		else
			printf("[P%d] %s wait: %ldms\n", ph->id, action, wait_time);
		pthread_mutex_unlock(&ph->sim->print_mutex);
	}
}

void	debug_fork_msg(t_philo *ph, const char *fork_name, time_t wait_time)
{
	if (DEBUG == true)
	{
		pthread_mutex_lock(&ph->sim->print_mutex);
		if (COLOR)
			printf("\033[0;35m[P%d] Got %s fork after %ldms\033[0m\n", ph->id,
				fork_name, wait_time);
		else
			printf("[P%d] Got %s fork after %ldms\n", ph->id, fork_name,
				wait_time);
		pthread_mutex_unlock(&ph->sim->print_mutex);
	}
}

// void	start_routine_debug(t_philo *ph)
// {
//     t_sim	*sim;
//     time_t  start_wait;
//     time_t  fork_wait;

//     sim = ph->sim;
//     start_wait = get_time_in_ms();
    
//     // Try to get first fork
//     pthread_mutex_lock(ph->left_fork);
//     fork_wait = get_time_in_ms() - start_wait;
//     debug_fork_msg(ph, "left", fork_wait);
//     routine_msg(MSG_FORK, ph);

//     // Try to get second fork
//     time_t second_start = get_time_in_ms();
//     pthread_mutex_lock(ph->right_fork);
//     fork_wait = get_time_in_ms() - second_start;
//     debug_fork_msg(ph, "right", fork_wait);
//     routine_msg(MSG_FORK, ph);

//     // Total waiting time for both forks
//     time_t total_wait = get_time_in_ms() - start_wait;
//     debug_time_msg(ph, "Total fork", total_wait);

//     routine_msg(MSG_EATING, ph);
//     pthread_mutex_lock(&ph->meal_lock);
//     ph->last_meal = get_time_in_ms();
//     pthread_mutex_unlock(&ph->meal_lock);
    
//     incremental_sleep(sim, sim->time_to_eat);
//     if (stop_sim(sim) == false)
//     {
//         pthread_mutex_lock(&ph->meal_lock);
//         ph->times_eaten++;
//         pthread_mutex_unlock(&ph->meal_lock);
//     }
    
//     routine_msg(MSG_SLEEPING, ph);
//     pthread_mutex_unlock(ph->left_fork);
//     pthread_mutex_unlock(ph->right_fork);
    
//     time_t cycle_time = get_time_in_ms() - start_wait;
//     debug_time_msg(ph, "Complete cycle", cycle_time);
    
//     incremental_sleep(sim, sim->time_to_sleep);
//     routine_msg(MSG_THINKING, ph);
// }

void	debug_philo_config(t_sim *sim, int i)
{
	printf("\n\033[0;36m=== Philosopher %d Configuration ===\033[0m\n", i + 1);
	printf("Position: %d\n", i);
	printf("Thread ID: %lu\n", sim->philo[i].th);
	printf("Philosopher ID: %d\n", sim->philo[i].id);
	printf("Left fork: %p (index: %d)\n", (void *)sim->philo[i].left_fork, i);
	printf("Right fork: %p (index: %d)\n", (void *)sim->philo[i].right_fork, (i
			+ 1) % sim->nb_philo);
	printf("Times eaten: %u\n", sim->philo[i].times_eaten);
	printf("Last meal time: %ld\n", sim->philo[i].last_meal);
	printf("Simulation parameters:\n");
	printf("  Time to die: %u\n", sim->time_to_die);
	printf("  Time to eat: %u\n", sim->time_to_eat);
	printf("  Time to sleep: %u\n", sim->time_to_sleep);
	printf("============================\n\n");
}

