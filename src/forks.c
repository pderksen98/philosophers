/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 11:49:43 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 12:06:41 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_philo_died(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->philo_died);
	if (s_philo->rules->philo_death == 1)
	{
		pthread_mutex_unlock(&s_philo->rules->philo_died);
		return (1);
	}
	pthread_mutex_unlock(&s_philo->rules->philo_died);
	return (0);
}

//First checks if an other philosopher died
//Than checks if current philosopher has to die
//If one of both cases: 1 is returned
//Else: 0 is returned
int	check_if_death(t_philo *s_philo)
{
	long	cur_time;

	cur_time = get_current_time();
	if (check_if_philo_died(s_philo))
		return (1);
	else if ((cur_time - s_philo->last_meal) > s_philo->rules->time_to_die)
	{
		printing("At %ld:	philo %d has died\n", s_philo);
		set_philo_dead(s_philo);
		return (1);
	}
	return (0);
}

//Sets the variable that an philosopher died to 1
void	set_philo_dead(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->philo_died);
	s_philo->rules->philo_death = 1;
	pthread_mutex_unlock(&s_philo->rules->philo_died);
}

void	put_down_forks(t_philo *s_philo, int left, int right)
{
	pthread_mutex_lock(&s_philo->rules->wait[left]);
	s_philo->rules->fork_available[left] = 0;
	pthread_mutex_unlock(&s_philo->rules->forks[left]);
	pthread_mutex_unlock(&s_philo->rules->wait[left]);
	pthread_mutex_lock(&s_philo->rules->wait[right]);
	s_philo->rules->fork_available[right] = 0;
	pthread_mutex_unlock(&s_philo->rules->forks[right]);
	pthread_mutex_unlock(&s_philo->rules->wait[right]);
	if (!check_times_eaten(s_philo))
		sleeping(s_philo);
}

int	pick_up_fork(t_philo *s_philo, int x)
{
	int	succes;

	pthread_mutex_lock(&s_philo->rules->wait[x]);
	if (s_philo->rules->fork_available[x] == 0)
	{
		s_philo->rules->fork_available[x] = 1;
		pthread_mutex_lock(&s_philo->rules->forks[x]);
		printing("At %ld:	philo %d has picked up a fork\n", s_philo);
		succes = 1;
	}
	else
		succes = 0;
	pthread_mutex_unlock(&s_philo->rules->wait[x]);
	return (succes);
}
