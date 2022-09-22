/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:25 by pderksen      #+#    #+#                 */
/*   Updated: 2022/09/21 11:55:24 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//writes string 's' to file descriptor 'fd'
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

//function that prints error message and returns (1)
int	ft_error(char *str)
{
	if (str)
		printf("%s", str);
	return (EXIT_FAILURE);
}
