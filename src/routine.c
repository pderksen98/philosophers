/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 16:30:49 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/19 18:27:48 by pieterderks   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_philo_died(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->philo_died);
	if (s_philo->rules->philo_death == 1)
	{
		pthread_mutex_unlock(&s_philo->rules->philo_died);
		return (1);
	}
	pthread_mutex_unlock(&s_philo->rules->philo_died);
	return (0);
}

//Sets the variable that an philosopher died to 1
void	set_philo_dead(t_philo *s_philo)
{
	pthread_mutex_lock(&s_philo->rules->philo_died);
	s_philo->rules->philo_death = 1; //kan je bool van maken (TRUE)
	pthread_mutex_unlock(&s_philo->rules->philo_died);
}

//First checks if an other philosopher died
//Than checks if current philosopher has to die
//If one of both cases: 1 is returned
//Else: 0 is returned
int	check_if_death(t_philo *s_philo)
{
	long	cur_time;

	cur_time = get_current_time();
	if (check_if_philo_died(s_philo))
		return (1);
	else if ((cur_time - s_philo->last_meal) > s_philo->rules->time_to_die)
	{
		printing("At %ld:	philo %d has died\n", s_philo);
		set_philo_dead(s_philo);
		return (1);
	}
	return (0);
}

void	sleeping(t_philo *s_philo)
{
	long	start_sleep;

	start_sleep = get_current_time();
	printing("At %ld:	philo %d is sleeping\n", s_philo);
	while (get_current_time() < (start_sleep + s_philo->rules->time_to_sleep))
		usleep(500);
	printing("At %ld:	philo %d is thinking\n", s_philo);
	try_to_eat(s_philo);
}

void	put_down_forks(t_philo *s_philo, int left, int right)
{
	pthread_mutex_lock(&s_philo->rules->wait[left]);
	s_philo->rules->fork_available[left] = 0;
	pthread_mutex_unlock(&s_philo->rules->forks[left]);
	pthread_mutex_unlock(&s_philo->rules->wait[left]);
	pthread_mutex_lock(&s_philo->rules->wait[right]);
	s_philo->rules->fork_available[right] = 0;
	pthread_mutex_unlock(&s_philo->rules->forks[right]);
	pthread_mutex_unlock(&s_philo->rules->wait[right]);
	printing("At %ld:	philo %d has put down both his forks\n", s_philo); //moet weg
	if (!check_times_eaten(s_philo))
		sleeping(s_philo);
}

void	eating(t_philo *s_philo)
{
	long	start_eat;

	start_eat = get_current_time();
	printing("At %ld:	philo %d is eating\n", s_philo);
	while (get_current_time() < (start_eat + s_philo->rules->time_to_eat))
		usleep(250);
	s_philo->last_meal = get_current_time();
	s_philo->times_eaten += 1;
	put_down_forks(s_philo, s_philo->left_fork, s_philo->right_fork);
}

//DATA RACE AT LINE 99
int	pick_up_fork(t_philo *s_philo, int x)
{
	int	succes;
	
	pthread_mutex_lock(&s_philo->rules->wait[x]);
	if (s_philo->rules->fork_available[x] == 0) //Read of size 4 at (addres) by thread T2 (MUteses: write M23, write M26)
	{
		s_philo->rules->fork_available[x] = 1;
		pthread_mutex_lock(&s_philo->rules->forks[x]);
		printing("At %ld:	philo %d has picked up a fork\n", s_philo);
		succes = 1;
	}
	else
		succes = 0;
	pthread_mutex_unlock(&s_philo->rules->wait[x]);
	return (succes);
}

int	check_times_eaten(t_philo *s_philo)
{
	if (s_philo->rules->nb_of_meals > 0)
	{
		if (s_philo->times_eaten == s_philo->rules->nb_of_meals)
			return (1);
	}
	return (0);
}

void	try_to_eat(t_philo *s_philo)
{
	while (!check_if_death(s_philo) && !check_times_eaten(s_philo))
	{
		if (pick_up_fork(s_philo, s_philo->left_fork))
		{
			while (!check_if_death(s_philo) && !check_times_eaten(s_philo))
			{
				if (pick_up_fork(s_philo, s_philo->right_fork))
					eating(s_philo);
				usleep(250);
			}
			return ;
		}
		usleep(250);
	}
	return ;
}

void	*ft_philosopher(void *void_philo)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)void_philo;
	if (s_philo->id %2)
		usleep((s_philo->rules->time_to_eat * 1000) / 2);
	try_to_eat(s_philo);
	return (void_philo);
}
