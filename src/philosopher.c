/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/14 17:06:03 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//TO DO LIST
//	- get try_lock working (create loop for mutex_struct aka forks)
//	- make this clean
//	- add check death function (also with rounds)
//	- make sure all threads stop when one is dead


void	printing(char *str, long time, t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->print_lock);
	printf(str, time, s_philo->id);
	pthread_mutex_unlock(&s_philo->rules->print_lock);
	
}

void	put_down_forks(t_philo *s_philo)
{
	long	put_down_time;
	
	put_down_time = get_current_time();
	printing("At %ld:	philo %d has put both forks down\n", time_dif(put_down_time, s_philo), s_philo);
	pthread_mutex_unlock(&s_philo->rules->forks[s_philo->left_fork]);
	pthread_mutex_unlock(&s_philo->rules->forks[s_philo->right_fork]);
	sleeping(s_philo);
}

void	thinking(t_philo *s_philo)
{
	long	think_time;

	think_time = get_current_time();
	printing("At %ld:	philo %d is thinking\n", time_dif(think_time, s_philo), s_philo);
	pick_up_forks(s_philo);
}

int	check_if_death(long current_time, t_philo *s_philo)
{
	if ((current_time - s_philo->last_meal) > s_philo->rules->time_to_die)
		return (1);
	return (0);
}

void	sleeping(t_philo *s_philo)
{
	long	start_sleep;

	start_sleep = get_current_time();
	printing("At %ld:	philo %d is sleeping\n", time_dif(start_sleep, s_philo), s_philo);
	while (get_current_time() < (start_sleep + s_philo->rules->time_to_sleep))
		usleep(500);
	thinking(s_philo);
}

void	pick_up_forks(t_philo *s_philo)
{
	long	pick_up_time;
	
	pthread_mutex_lock(&s_philo->rules->forks[s_philo->left_fork]);
	pthread_mutex_lock(&s_philo->rules->forks[s_philo->right_fork]);
	pick_up_time = get_current_time();
	printing("At %ld:	philo %d has picked both forks up\n", time_dif(pick_up_time, s_philo), s_philo);
	eating(s_philo);
}

void	eating(t_philo *s_philo)
{
	long	start_eat;

	start_eat = get_current_time();
	check_death(s_philo->last_meal, start_eat);
	printing("At %ld:	philo %d is eating\n", time_dif(start_eat, s_philo), s_philo);
	while (get_current_time() < (start_eat + s_philo->rules->time_to_eat))
		usleep(500);
	s_philo->last_meal = get_current_time();
	put_down_forks(s_philo);
}

int	try_to_eat(t_philo *s_philo)
{
	long	current_time;

	current_time = get_current_time();
	while (!check_if_death(current_time, s_philo))
	{
		
	}
}

void	*ft_philosopher(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	if (s_philo->id %2)
		usleep((s_philo->rules->time_to_eat * 1000) / 2);
	pick_up_forks(s_philo);
	return (void_philo);
}
 

// int	try_to_eat()
// {
// 	while (check_if_alive)
// 	{
// 		if (try_lock(left_fork))
// 		{
// 			printf("philosopher picked up left fork");
// 			while (check_if_alive)
// 			{
// 				if (try_lock(right_fork))
// 				{
// 					printf("philosopher picked up right fork");
// 					eating();
// 				}
// 			}
// 			return (1);
// 		}
// 	}		
// 	return (1);
// }



mutex_lock(check_fork)
{
	if (i == 0)
	{
		mutex_lock(fork)
		i = 1
		mutex_unlock(check_fork)
	}
	mutex_unlock(check_fork)
}