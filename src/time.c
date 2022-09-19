/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:33:56 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/19 16:54:45 by pieterderks   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

long	get_current_time(void)
{
	struct timeval	t;
	long			cur_time;

	gettimeofday(&t, NULL);
	cur_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (cur_time);
}
