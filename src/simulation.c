/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pieterderksen <pieterderksen@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:01:11 by pieterderks   #+#    #+#                 */
/*   Updated: 2022/09/06 14:15:42 by pieterderks   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//Sets the current time in mili seconds
//tv.sec = time in seconds
//tv.usec = additional time in micro seconds
int	get_start_time(t_rules *rules)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (ft_error("function: 'gettimeofday' returned an error\n"));
	rules->time_at_start = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (EXIT_SUCCESS);
}

int	start_simulation(t_rules *rules)
{
	if (get_start_time(rules))
		return (EXIT_FAILURE);
	


	return (EXIT_SUCCESS);
}