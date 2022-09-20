/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 17:05:20 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//function to sleep for the correct 'time_to_sleep' time
//when done philo is thinking and imidately will try to eat
//... again by calling the try to eat function
void	sleeping(t_philo *s_philo)
{
	long	start_sleep;

	start_sleep = get_current_time();
	printing("%ld:	philo %d is sleeping\n", s_philo);
	while (get_current_time() < (start_sleep + s_philo->rules->time_to_sleep))
		usleep(500);
	printing("%ld:	philo %d is thinking\n", s_philo);
	try_to_eat(s_philo);
}

//function to 'hold' both forks for correct 'time_to_eat' time
//when done it will set the 'last_meal' variable and calls the 
//... put_down_forks function
void	eating(t_philo *s_philo)
{
	long	start_eat;

	start_eat = get_current_time();
	printing("%ld:	philo %d is eating\n", s_philo);
	while (get_current_time() < (start_eat + s_philo->rules->time_to_eat))
		usleep(250);
	s_philo->last_meal = get_current_time();
	s_philo->times_eaten += 1;
	put_down_forks(s_philo, s_philo->left_fork, s_philo->right_fork);
}

//if the argument nb_of_meals is provided
//this function checkes if philo has reached this nb
//if yes (1) is returned else (0) is returned
int	check_times_eaten(t_philo *s_philo)
{
	if (s_philo->rules->nb_of_meals > 0)
	{
		if (s_philo->times_eaten == s_philo->rules->nb_of_meals)
			return (1);
	}
	return (0);
}

//function that try's to pick up forks
//loops each 0.250 [ms] while checking if another philo died or
//... if current philo has to die or if it has eaten enough
//if one of above is the case: the function returnes
//if it pickes up the left fork, it will go in the same loop again to
//... try to pick up the right fork
//if it has both forks -> eating function is called
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

//first function when threads are created
//to start of in shifts: if philo_nb is uneven: 
//.. philo's will wait for half of time_to_eat to try pick up forks
//if only 1 philo -> eating_single_philo is called
void	*ft_routine(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	if (s_philo->rules->nb_of_philos != 1)
	{
		if (s_philo->rules->time_to_die < s_philo->rules->time_to_eat)
		{
			if (s_philo->id % 2)
				usleep(250);
		}
		else if (s_philo->id % 2)
			usleep((s_philo->rules->time_to_eat * 1000) / 2);
		try_to_eat(s_philo);
	}
	else
		eating_single_philo(s_philo);
	return (void_philo);
}
