/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/09 14:31:34 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printing(char *str, t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->print_lock);
	printf(str, s_philo->id);
	pthread_mutex_unlock(&s_philo->rules->print_lock);
	
}

void	put_down_forks(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->forks[s_philo->left_fork]);
	s_philo->rules->fork_available[s_philo->left_fork] = 0;
	pthread_mutex_unlock(&s_philo->rules->forks[s_philo->left_fork]);
	pthread_mutex_lock(&s_philo->rules->forks[s_philo->right_fork]);
	s_philo->rules->fork_available[s_philo->right_fork] = 0;
	pthread_mutex_unlock(&s_philo->rules->forks[s_philo->right_fork]);
}

int	pick_up_forks(t_philo *s_philo)
{
	if (s_philo->rules->fork_available[s_philo->left_fork] == 0 && \
			s_philo->rules->fork_available[s_philo->right_fork] == 0)	
	{
		pthread_mutex_lock(&s_philo->rules->forks[s_philo->left_fork]);
		s_philo->rules->fork_available[s_philo->left_fork] = 1;
		pthread_mutex_unlock(&s_philo->rules->forks[s_philo->left_fork]);
		pthread_mutex_lock(&s_philo->rules->forks[s_philo->right_fork]);
		s_philo->rules->fork_available[s_philo->right_fork] = 1;
		pthread_mutex_unlock(&s_philo->rules->forks[s_philo->right_fork]);
		return (1);
	}
	return (0);
}

void	try_to_eat(t_philo *s_philo)
{
	while (1)
	{
		if (pick_up_forks(s_philo))
		{
			printing("Philo %d picked up both forks\n", s_philo);
			usleep(s_philo->rules->time_to_eat * 1000);
			put_down_forks(s_philo);
			printing("Philo %d has put both forks down\n", s_philo);
		}
		else
		{
			printing("Sleepy time for Philosopher %d\n", s_philo);
			usleep(5000);
		}
	}
}

void	*ft_philosopher(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	if (s_philo->id %2)
		usleep(1000);
	try_to_eat(s_philo);
	return (void_philo);
}
