/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 14:41:10 by pderksen      #+#    #+#                 */
/*   Updated: 2022/08/31 13:25:54 by pderksen      ########   odam.nl         */
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

typedef struct	s_input
{
	int	N;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	rounds;
	int	index;
}	t_input;

int		main(void);
int		ft_atoi(const char *str);
void	ft_check_malloc(void *ptr);
void	ft_putstr_fd(char *s, int fd);
#endif
