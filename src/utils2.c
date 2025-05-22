/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:49:55 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/14 11:39:51 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r');
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (convert_digits(str + i, sign));
}

int	convert_digits(const char *str, int sign)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}


int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
