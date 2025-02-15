/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:11:30 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 20:29:38 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	cub_check_draw(t_cub *cub, int x, int y)
{
	if (y < MINIMAP * (cub->map.minimap_size * 2 + 1) + STROKE && x < MINIMAP
		* (cub->map.minimap_size * 2 + 1) + STROKE)
		return (true);
	return (false);
}

void	cub_raycast_util_1(t_cub *cub)
{
	cub->raycast.line_height = (int)(cub->mlx.screen_size
			/ cub->raycast.perp_wall_dist);
	cub->raycast.draw_start = -cub->raycast.line_height / 2
		+ cub->mlx.screen_size / 2;
	if (cub->raycast.draw_start < 0)
		cub->raycast.draw_start = 0;
	cub->raycast.draw_end = cub->raycast.line_height / 2 + cub->mlx.screen_size
		/ 2;
	if (cub->raycast.draw_end >= cub->mlx.screen_size)
		cub->raycast.draw_end = cub->mlx.screen_size - 1;
	if (cub->raycast.side == 0)
		cub->raycast.wall_x = cub->player.pos_y + cub->raycast.perp_wall_dist
			* cub->raycast.ray_dir_y;
	else
		cub->raycast.wall_x = cub->player.pos_x + cub->raycast.perp_wall_dist
			* cub->raycast.ray_dir_x;
	cub->raycast.wall_x -= floor(cub->raycast.wall_x);
}

void	cub_raycast_draw_wall(t_cub *cub, t_img *img, int x)
{
	int				tex[2];
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;

	tex[0] = (int)(cub->raycast.wall_x * (double)img->width);
	if (cub->raycast.side == 0 && cub->raycast.ray_dir_x > 0)
		tex[0] = img->width - tex[0] - 1;
	if (cub->raycast.side == 1 && cub->raycast.ray_dir_y < 0)
		tex[0] = img->width - tex[0] - 1;
	step = 1.0 * img->height / cub->raycast.line_height;
	tex_pos = (cub->raycast.draw_start - cub->mlx.screen_size / 2
			+ cub->raycast.line_height / 2) * step;
	y = cub->raycast.draw_start - 1;
	while (++y < cub->raycast.draw_end)
	{
		tex[1] = (int)tex_pos & (img->height - 1);
		tex_pos += step;
		color = img->textures[img->width * tex[1] + tex[0]];
		if (!cub_check_draw(cub, x, y))
			cub_draw_pixel(&cub->img, x, y, color);
	}
}

void	cub_draw_floor_and_ceiling(t_cub *cub, int x)
{
	int	aux_y;

	aux_y = -1;
	while (++aux_y < cub->raycast.draw_start)
		if (!cub_check_draw(cub, x, aux_y))
			cub_draw_pixel(&cub->img, x, aux_y, cub->ceiling.hex);
	aux_y = cub->raycast.draw_end - 1;
	while (++aux_y < cub->mlx.screen_size - 1)
		if (!cub_check_draw(cub, x, aux_y))
			cub_draw_pixel(&cub->img, x, aux_y, cub->floor.hex);
}

t_img	*cub_get_wall(t_cub *cub)
{
	t_img	*img;

	if (cub->raycast.side == 0 && cub->raycast.ray_dir_x > 0)
		img = &cub->directions.south;
	else if (cub->raycast.side == 0 && cub->raycast.ray_dir_x < 0)
		img = &cub->directions.north;
	else if (cub->raycast.side == 1 && cub->raycast.ray_dir_y > 0)
		img = &cub->directions.east;
	else
		img = &cub->directions.west;
	return (img);
}
