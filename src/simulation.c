/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pieterderksen <pieterderksen@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:01:11 by pieterderks   #+#    #+#                 */
/*   Updated: 2022/09/20 16:46:31 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//funcion to create all the threads
//each thread(philo) gets the struct of the correct philosopher
//and each thread goes in to the ft_routine function to start
int	create_threads(t_philo *s_philo, t_rules *rules, \
			pthread_t *philo_thread)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_create(&philo_thread[i], NULL, ft_routine, \
			(void *)&s_philo[i]))
		{
			join_treads_error(philo_thread, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//function to set all the variables for each philosopher
//because philo's are dining at a round table:
//the right fork of last philo is same as left fork of first philo
void	create_philosophers(t_philo *s_philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		rules->fork_available[i] = 0;
		s_philo[i].rules = rules;
		s_philo[i].id = i + 1;
		s_philo[i].times_eaten = 0;
		s_philo[i].last_meal = rules->time_at_start;
		s_philo[i].left_fork = i;
		if (rules->nb_of_philos > 1)
		{
			if (s_philo[i].id != rules->nb_of_philos)
				s_philo[i].right_fork = i + 1;
			else
				s_philo[i].right_fork = 0;
		}
		i++;
	}
}

//joins the already made threads in case one fail to create
void	join_treads_error(pthread_t *philo_thread, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
}

//function to join all the threads used when simulation is done
void	join_threads(pthread_t *philo_thread, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
}

//mallocs all the t_philo structs necessary
//calls create_philosophers function
//calls create_threads function
//calls join_threads function
//frees the t_philo malloc
int	start_simulation(t_rules *rules)
{
	t_philo		*s_philo;
	pthread_t	philo_thread[200];

	s_philo = malloc(rules->nb_of_philos * sizeof(t_philo));
	if (!s_philo)
		return (ft_error("Failed to malloc s_philo struct\n"));
	create_philosophers(s_philo, rules);
	if (create_threads(s_philo, rules, philo_thread))
		return (EXIT_FAILURE);
	join_threads(philo_thread, rules);
	free(s_philo);
	return (EXIT_SUCCESS);
}
