/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 12:56:53 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/19 17:27:02 by pieterderks   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	init_mutexes(t_rules *rules)
{
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->philo_died, NULL);
}

int	initialize_rules(t_rules *rules, char **argv)
{
	if (init_rules(rules, argv))
		return (EXIT_FAILURE);
	if (check_input(rules))
		return (EXIT_FAILURE);
	init_mutexes(rules);
	return (EXIT_SUCCESS);
}
