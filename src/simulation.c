/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pieterderksen <pieterderksen@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:01:11 by pieterderks   #+#    #+#                 */
/*   Updated: 2022/09/14 17:04:43 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philosophers(t_philo *s_philo, t_rules *rules, \
		 pthread_t *philo_thread)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		rules->fork_available[i] = 0;
		s_philo[i].rules = rules;
		s_philo[i].id = i + 1;
		s_philo[i].times_eaten = 0;
		s_philo[i].start_time = get_current_time();
		s_philo[i].left_fork = i;
		if (rules->nb_of_philos > 1)
		{
			if (s_philo[i].id != rules->nb_of_philos)
				s_philo[i].right_fork = i + 1;
			else
				s_philo[i].right_fork = 0;
		}
		pthread_mutex_init(&rules->forks[i], NULL);
		pthread_create(&philo_thread[i], NULL, ft_philosopher, \
			(void *)&s_philo[i]);
		i++;
	}
}	

void	join_threads(pthread_t *philo_thread, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_of_philos)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
}

int	start_simulation(t_rules *rules)
{
	t_philo		*s_philo;
	pthread_t	philo_thread[rules->nb_of_philos]; //evt + 1

	s_philo = malloc(rules->nb_of_philos * sizeof(t_philo));
	if (!s_philo)
		return (ft_error("Failed to malloc s_philo struct\n"));
	create_philosophers(s_philo, rules, philo_thread);
	join_threads(philo_thread, rules);
	free(s_philo);
	return (EXIT_SUCCESS);
}
