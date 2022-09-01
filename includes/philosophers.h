/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:41:10 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/01 16:50:27 by pderksen      ########   odam.nl         */
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
# include "philosophers.h"



typedef struct s_rules
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	int				index;
	bool			a_philo_died;
	bool			all_philo_ate;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_philo	*philos;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_eaten;
	int				last_meal;
	bool			finished;
	t_rules			*rules;
}	t_philo;

int		main(int argc, char **argv);
int		ft_atoi(const char *str);
void	ft_check_malloc(void *ptr);
void	ft_putstr_fd(char *s, int fd);
int		ft_error(char *str);
int		initialize_all(t_rules *rules, char **argv);
int		initialize_rules(t_rules *rules, char **argv);
int		initialize_philos(t_rules *rules);
int		check_input(t_rules *rules);
#endif
