/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/15 17:22:30 by pderksen      ########   odam.nl         */
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

void	set_philo_dead(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->philo_died);
	s_philo->rules->philo_death = 1;
	pthread_mutex_unlock(&s_philo->rules->philo_died);
}

int	check_if_death(t_philo *s_philo)
{
	long	cur_time;

	cur_time = get_current_time();
	if ((cur_time - s_philo->last_meal) > s_philo->rules->time_to_die)
	{
		printing("At %ld:	philo %d has died\n", s_philo);
		return (1);
	}
	return (0);
}

void	sleeping(t_philo *s_philo)
{
	long	start_sleep;

	start_sleep = get_current_time();
	printing("At %ld:	philo %d is sleeping\n", s_philo);
	while (get_current_time() < (start_sleep + s_philo->rules->time_to_sleep))
		usleep(500);
	printing("At %ld:	philo %d is thinking\n", s_philo);
	try_to_eat(s_philo);
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
	printing("At %ld:	philo %d has put down both his forks\n", s_philo);
	sleeping(s_philo);
}

void	eating(t_philo *s_philo)
{
	long	start_eat;

	start_eat = get_current_time();
	printing("At %ld:	philo %d is eating\n", s_philo);
	while (get_current_time() < (start_eat + s_philo->rules->time_to_eat))
		usleep(250);
	s_philo->last_meal = get_current_time();
	put_down_forks(s_philo, s_philo->left_fork, s_philo->right_fork);
}

int	pick_up_fork(t_philo *s_philo, int x)
{
	int	succes;
	
	pthread_mutex_lock(&s_philo->rules->wait[x]);
	if (s_philo->rules->fork_available[x] == 0) //RACE CONDITION
	{
		printing("At %ld:	philo %d has picked up a fork\n", s_philo);
		s_philo->rules->fork_available[x] = 1;
		pthread_mutex_lock(&s_philo->rules->forks[x]);
		succes = 1;
	}
	else
		succes = 0;
	pthread_mutex_unlock(&s_philo->rules->wait[x]);
	return (succes);
}

void	try_to_eat(t_philo *s_philo)
{
	while (!check_if_death(s_philo) && !check_if_philo_died(s_philo))
	{
		if (pick_up_fork(s_philo, s_philo->left_fork))
		{
			while (!check_if_death(s_philo) && !check_if_philo_died(s_philo))
			{
				if (pick_up_fork(s_philo, s_philo->right_fork))
					eating(s_philo);
				usleep(250);
			}
			set_philo_dead(s_philo);
			return ;
		}
		usleep(250);
	}
	set_philo_dead(s_philo);
	return ;
}

void	*ft_philosopher(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	if (s_philo->id %2)
		usleep((s_philo->rules->time_to_eat * 1000) / 2);
	try_to_eat(s_philo);
	return (void_philo);
}
