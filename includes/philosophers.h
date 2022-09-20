/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:41:10 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/20 15:41:59 by pderksen      ########   odam.nl         */
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
	int				philo_death;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	wait[200];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	philo_died;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_eaten;
	long			last_meal;
	t_rules			*rules;
}	t_philo;

//atoi.c
int		ft_atoi(const char *str);
//destroy_mutexes.c
int		destroy_mutexes(t_rules *rules);
void	destroy_mutex_error(t_rules *rules, int x, int flag);
//initialize.c
int		check_input(t_rules *rules);
int		init_rules(t_rules *rules, char **argv);
int		init_mutexes(t_rules *rules);
int		initialize_rules(t_rules *rules, char **argv);
//main.c
int		main(int argc, char **argv);
//routine.c
void	sleeping(t_philo *s_philo);
void	eating(t_philo *s_philo);
int		check_times_eaten(t_philo *s_philo);
void	try_to_eat(t_philo *s_philo);
void	*ft_routine(void *void_philo);
//forks.c
int		check_if_philo_died(t_philo *s_philo);
int		check_if_death(t_philo *s_philo);
void	set_philo_dead(t_philo *s_philo);
void	put_down_forks(t_philo *s_philo, int left, int right);
int		pick_up_fork(t_philo *s_philo, int x);
//simulation.c
void	create_threads(t_philo *s_philo, t_rules *rules, \
			pthread_t *philo_thread);
void	create_philosophers(t_philo *s_philo, t_rules *rules);
void	join_threads(pthread_t *philo_thread, t_rules *rules);
int		start_simulation(t_rules *rules);
//time.c
void	eating_single_philo(t_philo *s_philo);
void	printing(char *str, t_philo *s_philo);
long	get_current_time(void);
//utils.c
void	ft_putstr_fd(char *s, int fd);
int		ft_error(char *str);
#endif
