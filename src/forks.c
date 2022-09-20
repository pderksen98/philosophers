/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 11:49:43 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 16:58:06 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//checks if a philosopher died
//if so -> (1) is returned
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

//first checks if an other philosopher died
//than checks if current philosopher has to die
//if one of both cases: (1) is returned
//else: (0) is returned
int	check_if_death(t_philo *s_philo)
{
	long	cur_time;

	cur_time = get_current_time();
	if (check_if_philo_died(s_philo))
		return (1);
	else if ((cur_time - s_philo->last_meal) > (s_philo->rules->time_to_die))
	{
		printing("%ld:	philo %d has died\n", s_philo);
		pthread_mutex_unlock(&s_philo->rules->forks[s_philo->left_fork]);
		set_philo_dead(s_philo);
		return (1);
	}
	return (0);
}

//sets the variable that a philosopher died to 1
void	set_philo_dead(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->philo_died);
	s_philo->rules->philo_death = 1;
	pthread_mutex_unlock(&s_philo->rules->philo_died);
}

//function to unlock both fork mutexes for the left and right fork
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

//function to check if a fork is available using the wait mutex
//if so it will lock the fork and return 1
//if not it will return 0
//the wait mutex is used to avoid philo's waiting a 
//...long time to lock a fork when it is already in use
int	pick_up_fork(t_philo *s_philo, int x)
{
	int	succes;

	pthread_mutex_lock(&s_philo->rules->wait[x]);
	if (s_philo->rules->fork_available[x] == 0)
	{
		s_philo->rules->fork_available[x] = 1;
		pthread_mutex_lock(&s_philo->rules->forks[x]);
		printing("%ld:	philo %d has picked up a fork\n", s_philo);
		succes = 1;
	}
	else
		succes = 0;
	pthread_mutex_unlock(&s_philo->rules->wait[x]);
	return (succes);
}
