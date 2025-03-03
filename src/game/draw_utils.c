/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:17:15 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 21:18:07 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	cub_check_angle(t_cub *cub, int x, int y)
{
	double	angle;

	angle = atan2(cub->player.dir_y, cub->player.dir_x) * 180 / PI - 90;
	if (angle < 0)
		angle += 360;
	if (angle >= 67.5 && angle < 112.5)
		return (x == 0 && (y > -PLAYER_SZ && y <= 0));
	if (angle >= 247.5 && angle < 292.5)
		return (x == 0 && (y >= 0 && y < PLAYER_SZ));
	if (angle >= 157.5 && angle < 202.5)
		return (y == 0 && (x > -PLAYER_SZ && x <= 0));
	if (angle >= 337.5 || angle < 22.5)
		return (y == 0 && (x >= 0 && x < PLAYER_SZ));
	if (angle >= 22.5 && angle < 67.5)
		return (x == -y && (x >= 0 && x < PLAYER_SZ));
	if (angle >= 112.5 && angle < 157.5)
		return (x == y && (x > -PLAYER_SZ && x <= 0));
	if (angle >= 202.5 && angle < 247.5)
		return (x == -y && (x > -PLAYER_SZ && x <= 0));
	if (angle >= 292.5 && angle < 337.5)
		return (x == y && (x >= 0 && x < PLAYER_SZ));
	return (false);
}

void	cub_check_pixel(t_cub *cub, int x, int y, bool erase)
{
	int		p[2];
	char	c;

	p[0] = (int)floor((cub->player.pos_x * MINIMAP + y) / MINIMAP);
	p[1] = (int)floor((cub->player.pos_y * MINIMAP + x) / MINIMAP);
	c = cub->map.map[p[0]][p[1]];
	if (!erase)
	{
		cub_draw_pixel(&cub->img, cub->tmp.x + x, cub->tmp.y + y, PLAYER_COLOR);
		if (cub_check_angle(cub, x, y))
			cub_draw_pixel(&cub->img, cub->tmp.x + x, cub->tmp.y + y,
				DIR_COLOR);
		return ;
	}
	if (c == '1')
		cub_draw_pixel(&cub->img, cub->tmp.x + x, cub->tmp.y + y, WALL_COLOR);
	else if (c == '-')
		cub_draw_pixel(&cub->img, cub->tmp.x + x, cub->tmp.y + y, EMPTY_COLOR);
	else
		cub_draw_pixel(&cub->img, cub->tmp.x + x, cub->tmp.y + y, FLOOR_COLOR);
}

void	cub_draw_player(t_cub *cub, bool erase)
{
	int	i;
	int	sum;
	int	j;

	i = PLAYER_SZ * -1 - 1;
	sum = 1;
	while (++i <= PLAYER_SZ)
	{
		j = PLAYER_SZ * -1 - 1;
		while (++j <= PLAYER_SZ)
			if (j >= (sum - 1) * -1 && j <= sum - 1)
				cub_check_pixel(cub, j, i, erase);
		if (i < 0)
			sum++;
		else
			sum--;
	}
}

void	cub_draw_square(t_cub *cub, int x, int y, unsigned int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINIMAP)
	{
		j = -1;
		while (++j < MINIMAP)
			cub_draw_pixel(&cub->img, x + i, y + j, color);
	}
}

void	cub_check_shape(t_cub *cub, int x, int y, char c)
{
	if (c == '1')
		cub_draw_square(cub, x * MINIMAP, y * MINIMAP, WALL_COLOR);
	else if (c == '-')
		cub_draw_square(cub, x * MINIMAP, y * MINIMAP, EMPTY_COLOR);
	else
		cub_draw_square(cub, x * MINIMAP, y * MINIMAP, FLOOR_COLOR);
}
