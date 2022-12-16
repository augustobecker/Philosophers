/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:40:51 by acesar-l          #+#    #+#             */
/*   Updated: 2022/12/16 03:59:28 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_longatoi(const char *str);
int    		ft_atoi(const char *str);
static int	ft_isblank(char a);
static int	ft_error(int sign);
static int	ft_isdigit(int argument);

long int	ft_longatoi(const char *str)
{
	long int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while (ft_isblank(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = (*str - 48) + nbr * 10;
		str++;
	}
	return (nbr * sign);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;
	int	nbr_len;

	nbr = 0;
	sign = 1;
	nbr_len = 0;
	while (ft_isblank(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (++nbr_len == 20)
			return (ft_error(sign));
		nbr = (*str - 48) + nbr * 10;
		str++;
	}
	return (nbr * sign);
}


static	int	ft_isblank(char a)
{
	return ((a == '\n')
		|| (a == '\v')
		|| (a == '\f')
		|| (a == '\t')
		|| (a == '\r')
		|| (a == ' '));
}

static	int	ft_error(int sign)
{
	if (sign > 0)
		return (-1);
	else
		return (0);
}

static int	ft_isdigit(int argument)
{
	return (argument >= '0' && argument <= '9');
}