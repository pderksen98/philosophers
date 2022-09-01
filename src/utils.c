/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:25 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/01 14:14:49 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_check_malloc(void *ptr)
{
	if (!ptr)
		exit(1);
}

int	ft_error(char *str)
{
	if (str)
		printf("%s", str);
	return (EXIT_FAILURE);
}
