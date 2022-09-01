/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:34 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/01 16:57:38 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philosophers(t_rules rules)
{
	int	i;

	i = 0;
	while (i < rules.nb_of_philos)
	{
		printf("Philosopher %d:\n", rules.philos[i].id);
		printf("	- left fork:  %d\n", rules.philos[i].left_fork);
		printf("	- right fork: %d\n", rules.philos[i].right_fork);
		i++;
	}
}

void	print_args(t_rules rules)
{
	printf("************  GENERAL RULES  ************\n");
	printf("# of philos:   %d\n", rules.nb_of_philos);
	printf("time to die:   %d [ms]\n", rules.time_to_die);
	printf("time to eat:   %d [ms]\n", rules.time_to_eat);
	printf("time to sleep: %d [ms]\n", rules.time_to_sleep);
	printf("# of meals:    %d\n", rules.nb_of_meals);
	printf("*****************************************\n\n");
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong amount of arguments\n"));
	if (initialize_all(&rules, argv))
		return (EXIT_FAILURE);
	print_args(rules);
	print_philosophers(rules);
	return (EXIT_SUCCESS);
}
