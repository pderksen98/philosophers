/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 12:56:53 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 15:43:18 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//checks if the input is correct
//if not it gives an error message and (1) is returned
int	check_input(t_rules *rules)
{
	if (rules->nb_of_philos < 1)
		return (ft_error("Number of philosophers must be at least 1\n"));
	if (rules->nb_of_philos > 200)
		return (ft_error("Program handles max 200 philosophers\n"));
	if (rules->time_to_die < 1)
		return (ft_error("Time to die must be larger than 0\n"));
	if (rules->time_to_eat < 1)
		return (ft_error("Time to eat must be larger than 0\n"));
	if (rules->time_to_sleep < 1)
		return (ft_error("Time to sleep must be larger than 0\n"));
	return (EXIT_SUCCESS);
}

//sets the input arguments in the 'rules' struct
//if no_of_meals is given it will set the variable accordingly
//if this value is not correct function returns (1)
//if the argument is not provided the value is set to (-1)
int	init_rules(t_rules *rules, char **argv)
{
	rules->time_at_start = get_current_time();
	rules->nb_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->philo_death = 0;
	if (argv[5])
	{
		rules->nb_of_meals = ft_atoi(argv[5]);
		if (rules->nb_of_meals < 1)
			return (ft_error("Number of times a philospher eats must be" \
					 " larger than 0 if it is given\n"));
	}
	else
		rules->nb_of_meals = -1;
	return (EXIT_SUCCESS);
}

//function that initializes all the necessary mutexes
//if an error occurs during the initizalization (1) is returned
int	init_mutexes(t_rules *rules)
{
	int	i;

	if (pthread_mutex_init(&rules->print_lock, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&rules->philo_died, NULL))
	{
		pthread_mutex_destroy(&rules->print_lock);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < rules->nb_of_philos)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
		{
			destroy_mutex_error(rules, i, 1);
			return (EXIT_FAILURE);
		}
		if (pthread_mutex_init(&rules->wait[i], NULL))
		{
			destroy_mutex_error(rules, i, 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//Calls all the initialize functions
//If an error occured of the init functions (1) returned
int	initialize_rules(t_rules *rules, char **argv)
{
	if (init_rules(rules, argv))
		return (EXIT_FAILURE);
	if (check_input(rules))
		return (EXIT_FAILURE);
	if (init_mutexes(rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
