/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/08 16:40:54 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosopher(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	printf("Philo ID from thread = %d\n", s_philo->id);
	return (void_philo);
}
