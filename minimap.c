/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:08:01 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/18 18:31:45 by avon-ben         ###   ########.fr       */
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

// -----------------------------------------------------------------------------


static void	draw_minimap(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (j < ft_strlen(map->map_arr[i]))
		{
			if (map->tiles[i][j]->is_wall)
				expand_walls(map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void	mk_rel_vals(t_map *map)
{
	double		p_x;
	double		p_y;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	p_x = map->player.x_coor;
	p_y = map->player.y_coor;
	while (map->tiles[i])
	{
		while (j < ft_strlen(map->map_arr[i]))
		{
			map->tiles[i][j]->rel_x = map->tiles[i][j]->x_coor - p_x;
			map->tiles[i][j]->rel_y = map->tiles[i][j]->y_coor - p_y;
			j++;
		}
		j = 0;
		i++;
	}
}

void	init_direction(t_map *map)
{
	if (map->player.start_direction == P_SOUTH)
		map->player.rot = (PI * 1.5);
	else if (map->player.start_direction == P_WEST)
		map->player.rot = PI;
	else if (map->player.start_direction == P_EAST)
		map->player.rot = 0;
	else
		map->player.rot = (0.5 * PI);
	map->player.x_angle = cos(map->player.rot);
	map->player.y_angle = -sin(map->player.rot);
}

void	init_rays(t_rays *rays)
{
	rays->ray_x = 0;
	rays->ray_y = 0;
	rays->vert_x = 0;
	rays->vert_y = 0;
	rays->ray_angle = 0;
	rays->offset_x = 0;
	rays->offset_y = 0;
	rays->dist_v = 0;
	rays->dist_h = 0;
}

void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_rays		*rays;
	mlx_image_t	*image;

	rays = malloc(sizeof(t_rays));
	map->rays = rays;
	init_rays(rays);
	map->mlx = mlx;
	map->img = img;
	image = mlx_new_image(map->mlx, MAX_X_MINIMAP - MIN_X_MINIMAP, \
		MAX_Y_MINIMAP - MIN_Y_MINIMAP);
	map->mini = image;
	if (!map->mini)
	{
		puts(mlx_strerror(mlx_errno));
		map_exit("Error\nmalloc Error\n");
	}
	draw_box(map);
	convert_coordinates(map);
}

void	draw_direction(t_map *map)
{
	int			i;
	double		x;
	double		y;

	x = get_mmap_centre_x();
	y = get_mmap_centre_y();
	i = 0;
	while (i < 20)
	{
		x += map->player.x_angle;
		y += map->player.y_angle;
		put_pixel_wrap(map->mini, (uint32_t)x, (uint32_t)y, \
		ft_pixel(0, 255, 0, 100));
		i++;
	}
}

void	ft_draw_player(void *param)
{
	t_map	*map;
	double	x;
	double	y;
	double	start_x;
	double	start_y;

	map = param;
	draw_background(map);
	start_x = (get_mmap_centre_x() - PLAYER_RAD);
	start_y = (get_mmap_centre_y() - PLAYER_RAD);
	x = start_x;
	y = start_y;
	draw_box(map);
	draw_minimap(map);
	while (x <= (start_x + (PLAYER_RAD * 2)))
	{
		while (y <= (start_y + (PLAYER_RAD * 2)))
			minimap_wrap_print(x, ++y, map, ft_pixel(0, 255, 0, 255));
		y = start_y;
		++x;
	}
	cast_rays(map);
	if (map->is_mini > 0)
		image_to_image(map->img, map->mini, 0, 0);
	draw_direction(map);
}

double FixAng(double a)
{
	if (a > (2 * PI))
		a -= (2 * PI);
	if (a < 0)
		a += (2 * PI);
	return (a);
}

int check_dir(t_map *map, size_t i, size_t j, double dir)
{
	double	xc;
	double	xa;
	double	yc;
	double	ya;

	xc = map->player.x_coor;
	xa = cos(FixAng(map->player.rot + dir));
	yc = map->player.y_coor;
	ya = -sin(FixAng(map->player.rot + dir));
	if ((map->tiles[i][j]->x_coor - 5) < (xc + (xa * MOVSPEED))
	&& (map->tiles[i][j]->x_coor + (TILE_RAD * 2) + 5) > (xc + (xa * MOVSPEED)) \
	&& (map->tiles[i][j]->y_coor - 5) < (yc + (ya * MOVSPEED) + 5) \
	&& (map->tiles[i][j]->y_coor + (TILE_RAD * 2) + 5) > (yc + (ya * MOVSPEED)))
		return (1);
	else
		return (0);
}

int	is_wall(t_map *map, double dir)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (j < ft_strlen(map->map_arr[i]))
		{
			if (dir == 0 && map->tiles[i][j]->is_wall && check_dir(map, i, j, 0))
				return (1);
			else if (dir == PI && map->tiles[i][j]->is_wall && \
			check_dir(map, i, j, PI))
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void slide(t_map *map, double dir)
{
	double store;

	store = map->player.x_angle;
	map->player.x_angle = 0;
	if (!is_wall(map, dir))
		map->player.y_coor += FixAng(map->player.y_angle * MOVSPEED);
	map->player.x_angle = store;
	store = map->player.y_angle;
	map->player.y_angle = 0;
	if (!is_wall(map, dir))
		map->player.x_coor += map->player.x_angle * MOVSPEED;
	map->player.y_angle = store;
}

void	move(t_map *map, double dir)
{
	double	store;
	double	x_angle;
	double	y_angle;
	

	x_angle = cos(FixAng(map->player.rot + dir));
	y_angle = -sin(FixAng(map->player.rot + dir));

	if (!is_wall(map, dir))
	{
		map->player.x_coor += (x_angle * MOVSPEED);
		map->player.y_coor += (y_angle * MOVSPEED);
	}
	else if (is_wall(map, dir))
		slide(map, dir);
	mk_rel_vals(map);
}

void mini_display(mlx_key_data_t keycode, void *param)
{
	// if (mlx_is_key_down(map->mlx, MLX_KEY_M))
	if (keycode.action == MLX_PRESS && keycode.key == MLX_KEY_M)
		*(int*)param *= -1;
}

// void strafe(t_map *map)
// {
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
// 	{

// 	}

// 	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
// }


void	ft_move_player(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
		move(map, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		move(map, PI);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player.rot = FixAng(map->player.rot + (ROTSPEED * (PI / 180)));
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player.rot = FixAng(map->player.rot - (ROTSPEED * (PI / 180)));
	mlx_key_hook(map->mlx, &mini_display, &map->is_mini);
	ft_draw_player(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A) || mlx_is_key_down(map->mlx, MLX_KEY_D))
		printf("a or d\n");
	map->player.x_angle = cos(map->player.rot);
	map->player.y_angle = -sin(map->player.rot);
}

// void	get_mini(t_map)

int32_t	draw_map(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	map->img = image;
	if (!map->img)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	make_minimap(map, mlx, image);
	mlx_loop_hook(mlx, ft_move_player, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
