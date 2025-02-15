/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_check_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:23:12 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 20:32:58 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	cub_draw_mmap_4(t_cub *cub, bool draw)
{
	const int	p[] = {cub->player.pos_x, cub->player.pos_y};
	const int	ct[] = {0, cub->map.height - (cub->map.minimap_size * 2 + 1)
		- 1, 0, -1};
	int			*t;

	t = (int *)ct;
	while (++t[3] < cub->map.minimap_size * 2 + 1)
	{
		++t[1];
		t[0] = -1;
		while (++t[0] < cub->map.minimap_size * 2 + 1)
		{
			if (draw)
				cub_check_shape(cub, t[0], t[3], cub->map.map[t[1]][t[0]]);
			if (t[1] == p[0] && t[0] == p[1])
			{
				cub->tmp.x = t[0] * MINIMAP;
				cub->tmp.y = t[3] * MINIMAP;
			}
		}
		cub_draw_last_column(cub, t[0], t[3]);
	}
	return (cub_draw_last_line(cub, t[0], t[3]), cub_small_update(cub));
}

void	cub_draw_mmap_5(t_cub *cub, bool draw)
{
	const int	p[] = {cub->player.pos_x, cub->player.pos_y};
	const int	ct[] = {0, cub->map.height - (cub->map.minimap_size * 2 + 1)
		- 1, 0, -1};
	int			*t;

	t = (int *)ct;
	while (++t[3] < cub->map.minimap_size * 2 + 1)
	{
		++t[1];
		t[2] = -1;
		t[0] = cub->map.width - (cub->map.minimap_size * 2 + 1) - 1;
		while (++t[2] < cub->map.minimap_size * 2 + 1)
		{
			++t[0];
			if (draw)
				cub_check_shape(cub, t[2], t[3], cub->map.map[t[1]][t[0]]);
			if (t[1] == p[0] && t[0] == p[1])
			{
				cub->tmp.x = t[2] * MINIMAP;
				cub->tmp.y = t[3] * MINIMAP;
			}
		}
		cub_draw_last_column(cub, t[2], t[3]);
	}
	return (cub_draw_last_line(cub, t[2], t[3]), cub_small_update(cub));
}

void	cub_draw_mmap_6(t_cub *cub, bool draw)
{
	const int	p[] = {cub->player.pos_x, cub->player.pos_y};
	const int	ct[] = {0, cub->map.height - (cub->map.minimap_size * 2 + 1)
		- 1, 0, -1};
	int			*t;

	t = (int *)ct;
	while (++t[3] < cub->map.minimap_size * 2 + 1)
	{
		++t[1];
		t[2] = -1;
		t[0] = p[1] - cub->map.minimap_size - 1;
		while (++t[0] < p[1] + cub->map.minimap_size + 1)
		{
			++t[2];
			if (draw)
				cub_check_shape(cub, t[2], t[3], cub->map.map[t[1]][t[0]]);
			if (t[1] == p[0] && t[0] == p[1])
			{
				cub->tmp.x = t[2] * MINIMAP;
				cub->tmp.y = t[3] * MINIMAP;
			}
		}
		cub_draw_last_column(cub, t[2] + 1, t[3]);
	}
	return (cub_draw_last_line(cub, t[2] + 1, t[3]), cub_small_update(cub));
}

void	cub_mmap_check_2(t_cub *cub, bool draw)
{
	if ((int)cub->player.pos_y - cub->map.minimap_size < 0)
		return (cub_draw_mmap_4(cub, draw));
	if ((int)cub->player.pos_y + cub->map.minimap_size > cub->map.width - 1)
		return (cub_draw_mmap_5(cub, draw));
	return (cub_draw_mmap_6(cub, draw));
}
