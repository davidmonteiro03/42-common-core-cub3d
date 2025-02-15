/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:31:45 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 20:30:58 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

unsigned long	ft_min(unsigned long a, unsigned long b)
{
	if (a < b)
		return (a);
	return (b);
}

unsigned long	ft_max(unsigned long a, unsigned long b)
{
	if (a > b)
		return (a);
	return (b);
}

long int	cub_atol(const char *nptr)
{
	long int	num;
	long int	sign;
	size_t		i;

	num = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		num = num * 10 + nptr[i++] - '0';
	return (num * sign);
}

unsigned int	cub_convert_to_rgb(unsigned int value)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (value >> 16) & 0xFF;
	g = (value >> 8) & 0xFF;
	b = value & 0xFF;
	return (r << 16 | g << 8 | b);
}

double	cub_double_abs(double num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}
