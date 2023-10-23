/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:16:25 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/23 18:37:57 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mlx/include/MLX42/MLX42.h"
#include "mlx/include/KHR/khrplatform.h"
#include "map.h"
#include "libft/libft.h"
#include "defines.h"
#include <math.h>

void	mini_display(mlx_key_data_t keycode, void *param)
{
	if (keycode.action == MLX_PRESS && keycode.key == MLX_KEY_M)
		*(int *)param *= -1;
}

void	ft_move_player(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
		move(map, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		move(map, PI);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player.rot = fixang(map->player.rot + (ROTSPEED * (PI / 180)));
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player.rot = fixang(map->player.rot - (ROTSPEED * (PI / 180)));
	mlx_key_hook(map->mlx, &mini_display, &map->is_mini);
	ft_draw_player(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		move(map, (PI * 1.5));
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		move(map, (PI * 0.5));
	map->player.x_angle = cos(map->player.rot);
	map->player.y_angle = -sin(map->player.rot);
}

int	check_dir(t_map *map, size_t i, size_t j, double dir)
{
	double	xc;
	double	xa;
	double	yc;
	double	ya;

	xc = map->player.x_coor;
	xa = cos(fixang(map->player.rot + dir));
	yc = map->player.y_coor;
	ya = -sin(fixang(map->player.rot + dir));
	if ((map->tiles[i][j]->x_coor - 5) < (xc + (xa * MOVSPEED))
	&& (map->tiles[i][j]->x_coor + (TILE_RAD * 2) + 5) > (xc + (xa * MOVSPEED)) \
	&& (map->tiles[i][j]->y_coor - 5) < (yc + (ya * MOVSPEED) + 5) \
	&& (map->tiles[i][j]->y_coor + (TILE_RAD * 2) + 5) > (yc + (ya * MOVSPEED)))
		return (1);
	else
		return (0);
}

int	check_wall_pos(t_map *map, size_t pos_x, size_t pos_y)
{
	if (map->tiles[pos_y][pos_x] && map->tiles[pos_y][pos_x]->is_wall)
		return (1);
	else
		return (0);
}

void	move(t_map *map, double dir)
{
	double	x_angle;
	double	y_angle;
	double	x_update;
	double	y_update;

	x_angle = cos(fixang(map->player.rot + dir));
	y_angle = -sin(fixang(map->player.rot + dir));
	x_update = map->player.x_coor + (x_angle * MOVSPEED);
	y_update = map->player.y_coor + (y_angle * MOVSPEED);
	if (!check_wall_pos(map, (x_update / TD), map->player.y_coor / TD) && \
	!check_wall_pos(map, ((x_update + PLAYER_RAD) / TD), \
	(map->player.y_coor + PLAYER_RAD) / TD))
		map->player.x_coor = x_update;
	if (!check_wall_pos(map, (map->player.x_coor / TD), (y_update / TD)) && \
	!check_wall_pos(map, ((map->player.x_coor + PLAYER_RAD) / TD), \
	((y_update + PLAYER_RAD) / TD)))
		map->player.y_coor = y_update;
	mk_rel_vals(map);
}
