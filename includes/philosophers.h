/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:41:10 by pderksen      #+#    #+#                 */
/*   Updated: 2022/08/31 15:17:33 by pderksen      ########   odam.nl         */
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
# include "philosophers.h"

typedef struct	s_rules
{
	int	N;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	rounds;
	int	index;
}	t_rules;

typedef struct	s_philo
{
	int		philo_id;
	int		left_fork;
	int		right_fork;
	int		times_eaten;
	t_rules	*rules;
}	t_philo;

int		main(int argc, char **argv);
int		ft_atoi(const char *str);
void	ft_check_malloc(void *ptr);
void	ft_putstr_fd(char *s, int fd);
#endif
