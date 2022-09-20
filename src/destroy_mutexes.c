/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mutexes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 14:08:09 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 15:43:28 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//when no error occured during the initialization of the mutexes
//all the uesed mutexes are destroyed in this function
int	destroy_mutexes(t_rules *rules)
{
	int	i;

	if (pthread_mutex_destroy(&rules->print_lock))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&rules->philo_died))
		return (EXIT_FAILURE);
	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_mutex_destroy(&rules->forks[i]))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&rules->wait[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

//if an error occured during the initialization of one of the mutexes
//all the so far initialized mutexes are destroyed in this function
void	destroy_mutex_error(t_rules *rules, int x, int flag)
{
	int	i;

	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->philo_died);
	i = 0;
	while (i <= x)
	{
		if (i != x)
		{
			pthread_mutex_destroy(&rules->forks[i]);
			pthread_mutex_destroy(&rules->wait[i]);
		}
		else
		{
			if (flag == 2)
				pthread_mutex_destroy(&rules->forks[i]);
		}
		i++;
	}
}
