/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 12:56:53 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/08 16:38:06 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(t_rules *rules)
{
	if (rules->nb_of_philos < 1)
		return (ft_error("Number of philosophers must be at least 1\n"));
	if (rules->nb_of_philos > 200)
		return (ft_error("Program handles max 200 philosophers\n"));
	if (rules->time_to_die < 0)
		return (ft_error("Time to die must be positive\n"));
	if (rules->time_to_eat < 0)
		return (ft_error("Time to eat must be positive\n"));
	if (rules->time_to_sleep < 0)
		return (ft_error("Time to sleep must be positive\n"));
	return (EXIT_SUCCESS);
}

int	init_rules(t_rules *rules, char **argv)
{
	rules->time_at_start = get_current_time();
	rules->nb_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		rules->nb_of_meals = ft_atoi(argv[5]);
		if (rules->nb_of_meals < 0)
			return (ft_error("Number of times a philospher eats must be" \
					 "positive if it is given\n"));
	}
	else
		rules->nb_of_meals = -1;
	return (EXIT_SUCCESS);
}

int	initialize_rules(t_rules *rules, char **argv)
{
	if (init_rules(rules, argv))
		return (EXIT_FAILURE);
	if (check_input(rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
