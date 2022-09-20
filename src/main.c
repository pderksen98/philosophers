/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:34 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 12:01:24 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//TO DO
// - protect all mutex_init and thread_create and free in the end
int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		return (ft_error("Wrong amount of arguments\n"));
	if (initialize_rules(&rules, argv))
		return (EXIT_FAILURE);
	if (start_simulation(&rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
