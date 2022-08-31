/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:34 by pderksen      #+#    #+#                 */
/*   Updated: 2022/08/31 16:04:44 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialize_rules(t_rules *rules, char **argv)
{
	


	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	
	if (argc < 5 || argc > 6)
		ft_error("Wrong amount of arguments\n");
	if (initialize_rules(&rules, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
