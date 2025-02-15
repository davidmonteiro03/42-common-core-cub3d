/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:31:19 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 21:22:03 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*cub_buildfree(char *s1, char *s2, char *(*f)(const char *,
			const char *))
{
	char	*str;

	str = f(s1, s2);
	free(s1);
	free(s2);
	return (str);
}
