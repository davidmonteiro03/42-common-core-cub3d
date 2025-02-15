/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:54:02 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 21:09:53 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbru(unsigned int num)
{
	char	*str;
	int		len;

	str = ft_utoa(num);
	len = ft_putstr(str);
	free(str);
	return (len);
}
