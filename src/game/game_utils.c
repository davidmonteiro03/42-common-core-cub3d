/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:41:57 by dcaetano          #+#    #+#             */
/*   Updated: 2025/02/15 21:18:13 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	cub_draw_pixel(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int *)(img->addr + (x * img->bpp / 8) + (y
				* img->size_line)) = color;
}

void	cub_mmap_check(t_cub *cub, bool draw)
{
	if ((int)cub->player.pos_x - cub->map.minimap_size < 0)
		cub_mmap_check_1(cub, draw);
	else if ((int)cub->player.pos_x + cub->map.minimap_size > cub->map.height
		- 1)
		cub_mmap_check_2(cub, draw);
	else
		cub_mmap_check_3(cub, draw);
}

void	cub_update_angle(t_cub *cub, int angle)
{
	double	old_dir_x;
	double	old_plane_x;

	cub_draw_player(cub, true);
	old_dir_x = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(cub->player.rot_speed * angle)
		- cub->player.dir_y * sin(cub->player.rot_speed * angle);
	cub->player.dir_y = old_dir_x * sin(cub->player.rot_speed * angle)
		+ cub->player.dir_y * cos(cub->player.rot_speed * angle);
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(cub->player.rot_speed
			* angle) - cub->player.plane_y * sin(cub->player.rot_speed * angle);
	cub->player.plane_y = old_plane_x * sin(cub->player.rot_speed * angle)
		+ cub->player.plane_y * cos(cub->player.rot_speed * angle);
	cub_draw_player(cub, false);
}

void	cub_move_player(t_cub *cub, double x, double y)
{
	char	c[2];
	int		old[2];
	int		new[2];

	if (fabs(x) >= 1.0)
		x = x - (int)x;
	if (fabs(y) >= 1.0)
		y = y - (int)y;
	cub_draw_player(cub, true);
	c[0] = cub->map.map[(int)(cub->player.pos_x + x)][(int)cub->player.pos_y];
	c[1] = cub->map.map[(int)cub->player.pos_x][(int)(cub->player.pos_y + y)];
	old[0] = (int)cub->player.pos_x;
	old[1] = (int)cub->player.pos_y;
	if (c[0] != '1' && c[0] != '-')
		cub->player.pos_x += x;
	if (c[1] != '1' && c[1] != '-')
		cub->player.pos_y += y;
	new[0] = (int)cub->player.pos_x;
	new[1] = (int)cub->player.pos_y;
	if (old[0] != new[0] || old[1] != new[1])
		cub_mmap_check(cub, true);
	else
		cub_mmap_check(cub, false);
	cub_draw_player(cub, false);
}

void	cub_check_keys(t_cub *cub, int x, int y)
{
	if (cub->keys.esc)
		cub_exit(cub);
	if (cub->keys.right || (x > cub->mlx.screen_size - 200
			&& x < cub->mlx.screen_size && y > 0 && y < cub->mlx.screen_size))
		cub_update_angle(cub, -1);
	if (cub->keys.left || (x > 0 && x < 200 && y > 0
			&& y < cub->mlx.screen_size))
		cub_update_angle(cub, 1);
	if (cub->keys.w)
		cub_move_player(cub, cub->player.dir_x * cub->player.move_speed,
			cub->player.dir_y * cub->player.move_speed);
	if (cub->keys.s)
		cub_move_player(cub, cub->player.dir_x * -cub->player.move_speed,
			cub->player.dir_y * -cub->player.move_speed);
	if (cub->keys.a)
		cub_move_player(cub, cub->player.dir_y * -cub->player.move_speed,
			cub->player.dir_x * cub->player.move_speed);
	if (cub->keys.d)
		cub_move_player(cub, cub->player.dir_y * cub->player.move_speed,
			cub->player.dir_x * -cub->player.move_speed);
}
