/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:34 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 15:44:28 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//checks if correct number of arguments
//calls initialize_rules; start simulation and destroy_mutex function
//if an error occured in one of the functions program stops and (1) is returned
int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong amount of arguments\n"));
	if (initialize_rules(&rules, argv))
		return (EXIT_FAILURE);
	if (start_simulation(&rules))
		return (EXIT_FAILURE);
	if (destroy_mutexes(&rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
