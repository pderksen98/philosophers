/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:33:56 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 15:45:23 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//hard code when only one philosopher
void	eating_single_philo(t_philo *s_philo)
{
	long	pick_fork;

	printing("%ld:	philo %d has picked up a fork\n", s_philo);
	pick_fork = get_current_time();
	while (get_current_time() < (pick_fork + s_philo->rules->time_to_die))
		usleep(250);
	printing("%ld:	philo %d has died\n", s_philo);
}

//function in order to print the messages
//cur_time is the current time, sim_time is cur_time - time sim started
void	printing(char *str, t_philo *s_philo)
{
	long	cur_time;
	long	sim_time;

	pthread_mutex_lock(&s_philo->rules->print_lock);
	if (!check_if_philo_died(s_philo))
	{
		cur_time = get_current_time();
		sim_time = cur_time - s_philo->rules->time_at_start;
		printf(str, sim_time, s_philo->id);
	}
	pthread_mutex_unlock(&s_philo->rules->print_lock);
}

//function to get the current time in mili seconds
//this by multiplying time in seconds by 1000 and
//... adding the addidional microseconds devided by 1000
long	get_current_time(void)
{
	struct timeval	t;
	long			cur_time;

	gettimeofday(&t, NULL);
	cur_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (cur_time);
}
