/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:41:10 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/09 14:23:16 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h> //write
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <time.h>
# include <sys/errno.h>
# include <stdbool.h>
# include <sys/time.h>
# include "philosophers.h"

typedef struct s_rules
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	long			time_at_start;
	int				fork_available[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print_lock;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_eaten;
	long			start_time;
	t_rules			*rules;
}	t_philo;

int		main(int argc, char **argv);
int		ft_atoi(const char *str);
void	ft_check_malloc(void *ptr);
void	ft_putstr_fd(char *s, int fd);
int		ft_error(char *str);
int		initialize_rules(t_rules *rules, char **argv);
int		init_rules(t_rules *rules, char **argv);
int		check_input(t_rules *rules);
int		start_simulation(t_rules *rules);
void	create_philosophers(t_philo *s_philo, t_rules *rules, \
		pthread_t *philo_thread);
void	join_threads(pthread_t *philo_thread, t_rules *rules);
long	get_current_time(void);
void	*ft_philosopher(void *void_philo);
#endif
