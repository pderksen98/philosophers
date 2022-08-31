/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atoi.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:15:05 by pderksen      #+#    #+#                 */
/*   Updated: 2022/08/31 13:51:41 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_power(int ground, int power)
{
	long long	value;

	value = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (value);
	while (power)
	{
		value *= ground;
		power--;
	}
	return (value);
}

long long	ft_atoi_calc(const char *str, int len)
{
	int			i;
	long long	atoi;

	i = 0;
	atoi = 0;
	while (len)
	{
		atoi += ((str[len - 1] - '0') * ft_power(10, i));
		i++;
		len--;
	}
	return (atoi);
}

static void	error_message(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

int	check_atoi_int(long long ll_atoi)
{
	if (ll_atoi > INT_MAX)
		error_message();
	else if (ll_atoi < INT_MIN)
		error_message();
	return ((int)ll_atoi);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;

	neg = 1;
	while (*str == '\t' || *str == '\n' || \
	*str == '\v' || *str == '\f' || \
	*str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		i++;
	}
	return (check_atoi_int(ft_atoi_calc(str, i) * neg));
}
