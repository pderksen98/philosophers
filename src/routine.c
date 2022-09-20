/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 12:06:57 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	eating(t_philo *s_philo)
{
	long	start_eat;

	start_eat = get_current_time();
	printing("At %ld:	philo %d is eating\n", s_philo);
	while (get_current_time() < (start_eat + s_philo->rules->time_to_eat))
		usleep(250);
	s_philo->last_meal = get_current_time();
	s_philo->times_eaten += 1;
	put_down_forks(s_philo, s_philo->left_fork, s_philo->right_fork);
}

int	check_times_eaten(t_philo *s_philo)
{
	if (s_philo->rules->nb_of_meals > 0)
	{
		if (s_philo->times_eaten == s_philo->rules->nb_of_meals)
			return (1);
	}
	return (0);
}

void	try_to_eat(t_philo *s_philo)
{
	while (!check_if_death(s_philo) && !check_times_eaten(s_philo))
	{
		if (pick_up_fork(s_philo, s_philo->left_fork))
		{
			while (!check_if_death(s_philo) && !check_times_eaten(s_philo))
			{
				if (pick_up_fork(s_philo, s_philo->right_fork))
					eating(s_philo);
				usleep(250);
			}
			return ;
		}
		usleep(250);
	}
	return ;
}

void	*ft_philosopher(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	if (s_philo->rules->nb_of_philos != 1)
	{
		if (s_philo->id % 2)
			usleep((s_philo->rules->time_to_eat * 1000) / 2);
		try_to_eat(s_philo);
	}
	else
		eating_single_philo(s_philo);
	return (void_philo);
}
