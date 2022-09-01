/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 12:56:53 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/01 16:50:36 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(t_rules *rules)
{
	if (rules->nb_of_philos <= 0 || rules->time_to_die <= 0 \
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0 \
		|| rules->nb_of_meals < 0)
		return (ft_error("Input values must be larger than 0\n"));
	if (rules->nb_of_philos > 200)
		return (ft_error("Program handles max 200 philosophers\n"));
	return (EXIT_SUCCESS);
}

int	initialize_rules(t_rules *rules, char **argv)
{
	rules->nb_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		rules->nb_of_meals = ft_atoi(argv[5]);
		if (rules->nb_of_meals == 0)
			return (ft_error("Input values must be larger than 0\n"));
	}
	else
		rules->nb_of_meals = 0;
	rules->all_philo_ate = false;
	rules->a_philo_died = false;
	return (EXIT_SUCCESS);
}

int	initialize_philos(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = malloc(rules->nb_of_philos * sizeof(*philo));
	if (!philo)
		return (ft_error("Malloc went wrong\n"));
	i = 0;
	while (i < rules->nb_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = i;
		philo[i].left_fork = (i + 1) % rules->nb_of_philos;
		philo[i].times_eaten = 0;
		philo[i].last_meal = 0;
		philo[i].finished = false;
		philo[i].rules = rules;
		i++;
	}
	rules->philos = philo;
	return (EXIT_SUCCESS);
}

int	initialize_all(t_rules *rules, char **argv)
{
	if (initialize_rules(rules, argv))
		return (EXIT_FAILURE);
	if (check_input(rules))
		return (EXIT_FAILURE);
	if (initialize_philos(rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
