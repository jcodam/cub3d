// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   rays.c                                             :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/14 19:05:55 by avon-ben      #+#    #+#                 */
// /*   Updated: 2023/08/14 19:23:19 by avon-ben      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "map.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
#include <stdlib.h>

//---------------------------Draw Rays and Walls--------------------------------

// void	draw_line(t_map *map, float int_x, float int_y)
// {
// 	minimap_wrap_print(mini_x(map, map->rays->draw_x), \
// 	mini_y(map, map->rays->draw_y), map, ft_pixel(0, 0, 255, 200));
// 	map->rays->draw_x += int_x;
// 	map->rays->draw_y += int_y;
// 	map->rays->dist_y -= int_y;
// }

// static void	draw_ray(t_map *map)
// {
// 	float	int_x;
// 	float	int_y;

// 	map->rays->draw_x = map->player.x_coor;
// 	map->rays->draw_y = map->player.y_coor;
// 	map->rays->dist_x = (map->rays->ray_x - map->player.x_coor);
// 	map->rays->dist_y = (map->rays->ray_y - map->player.y_coor);
// 	int_x = map->rays->dist_x / 1000;
// 	int_y = map->rays->dist_y / 1000;
// 	if (map->rays->dist_x == 0 || map->rays->dist_y == 0)
// 		return ;
// 	if (map->rays->dist_h <= map->rays->dist_h)
// 	{
// 		if (map->rays->dist_y > 0)
// 		{
// 			while (map->rays->dist_y > 0)
// 				draw_line(map, int_x, int_y);
// 		}
// 		else if ((map->rays->dist_y < 0))
// 		{
// 			while (map->rays->dist_y < 0)
// 				draw_line(map, int_x, int_y);
// 		}
// 	}
// }

void	move_to_next_point_h(t_map *map)
{
	if (((int)map->rays->ray_x / 64) <= 0 || ((int)map->rays->ray_x/ 64) \
	>= (map->width) || ((int)map->rays->ray_y / 64) <= 0 || \
	((int)map->rays->ray_y / 64) >= (map->height) || \
	map->tiles[((int)map->rays->ray_y / 64)] \
	[((int)map->rays->ray_x / 64)]->is_wall)
	{
		map->rays->dof = 8;
		map->rays->dist_h = cos(degToRad(map->rays->ray_angle)) * \
		(map->rays->ray_x - map->player.x_coor) - \
		sin(degToRad(map->rays->ray_angle)) * \
		(map->rays->ray_y - map->player.y_coor);
	}
	else
	{
		map->rays->ray_x += map->rays->offset_x;
		map->rays->ray_y += map->rays->offset_y;
		map->rays->dof++;
	}
}

void	move_to_next_point_v(t_map *map)
{
	if (((int)map->rays->vert_x / 64) <= 0 || ((int)map->rays->vert_x / 64) \
	>= (map->width) || ((int)map->rays->vert_y / 64) <= 0 || \
	((int)map->rays->vert_y / 64) >= (map->height) || \
	map->tiles[((int)map->rays->vert_y / 64)] \
	[((int)map->rays->vert_x / 64)]->is_wall)
	{
		map->rays->dof = 8;
		map->rays->dist_v = cos(degToRad(map->rays->ray_angle)) * \
		(map->rays->vert_x - map->player.x_coor) - \
		sin(degToRad(map->rays->ray_angle)) * \
		(map->rays->vert_y - map->player.y_coor);
	}
	else
	{
		map->rays->vert_x += map->rays->offset_x;
		map->rays->vert_y += map->rays->offset_y;
		map->rays->dof++;
	}
}

void	set_streight_line(t_map *map)
{
	map->rays->vert_x = map->player.x_coor;
	map->rays->vert_y = map->player.y_coor;
	map->rays->dof = 8;
}

void	vert_right(t_map *map, float Tan)
{
	map->rays->vert_x = (((int)map->player.x_coor / (2 * TILE_RAD)) * \
	(2 * TILE_RAD) + (2 * TILE_RAD));
	map->rays->vert_y = (map->player.x_coor - map->rays->vert_x) * Tan + \
	map->player.y_coor;
	map->rays->offset_x = (2 * TILE_RAD);
	map->rays->offset_y = (map->rays->offset_x * -1) * Tan;
}

void	vert_left(t_map *map, float Tan)
{
	map->rays->vert_x = (((int)map->player.x_coor / (2 * TILE_RAD)) * \
	(2 * TILE_RAD)) - 0.0001;
	map->rays->vert_y = (map->player.x_coor - map->rays->vert_x) * Tan + \
	map->player.y_coor;
	map->rays->offset_x = -1 * (2 * TILE_RAD);
	map->rays->offset_y = (map->rays->offset_x * -1) * Tan;
}

void	hor_up(t_map *map, float Tan)
{
	map->rays->ray_y = (((int)map->player.y_coor / (2 * TILE_RAD)) * \
	(2 * TILE_RAD) - 0.0001);
	map->rays->ray_x = (map->player.y_coor - map->rays->ray_y) * (1.0 / Tan) + \
	map->player.x_coor;
	map->rays->offset_y = -1 * (2 * TILE_RAD);
	map->rays->offset_x = (-1 * map->rays->offset_y) * (1.0 / Tan);
}

void hor_down(t_map *map, float Tan)
{
	map->rays->ray_y = (((int)map->player.y_coor / (2 * TILE_RAD)) * \
	(2 * TILE_RAD) + (2 * TILE_RAD));
	map->rays->ray_x = (map->player.y_coor - map->rays->ray_y) * \
	(1.0 / Tan) + map->player.x_coor;
	map->rays->offset_y = (2 * TILE_RAD);
	map->rays->offset_x = (-1 * map->rays->offset_y) * (1.0 / Tan);
}

void rays_vertical(t_map *map, float Tan)
{
	map->rays->dof = 0;
	map->rays->dist_v = 100000;
	if (map->rays->ray_angle < 90 || map->rays->ray_angle > 270)
		vert_right(map, Tan);
	else if (map->rays->ray_angle > 90 && map->rays->ray_angle < 270)
		vert_left(map, Tan);
	else
		set_streight_line(map);
	while (map->rays->dof < 8)
		move_to_next_point_v(map);
}

void rays_horizontal(t_map *map, float Tan)
{
	map->rays->dist_h = 100000;
	map->rays->dof = 0;
	if (sin(degToRad(map->rays->ray_angle)) > 0.0001)
		hor_up(map, Tan);
	else if (sin(degToRad(map->rays->ray_angle)) < 0.0001)
		hor_down(map, Tan);
	else
		set_streight_line(map);
	while (map->rays->dof < 8)
		move_to_next_point_h(map);
}

void draw_vert_line(t_map *map, int height, int width, int start_y, int pos)
{
	int	x;
	int	y;
	int start_x;

	x = pos;
	start_x = x;
	y = start_y;
	while (x < (start_x +width) && x < WIDTH)
	{
		while (y < height)
		{
			put_pixel_wrap(map->img, x, y, ft_pixel(0, 255, 0, 150));
			y++;
		}
		y = start_y;
		x++;
	}
}

int	cast_rays(t_map *map)
{
	float	tang;
	int		i;
	int		lineH;
	float	line_int;
	float	ray_int;

	ray_int = (FOV * 4)/ WIDTH;
	line_int = (WIDTH / (FOV * 4));
	i = 0;
	map->rays->ray_angle = map->player.rotation + FOV;
	while (i < WIDTH)
	{
		tang = tan((degToRad(map->rays->ray_angle)));
		rays_vertical(map, tang);
		rays_horizontal(map, tang);
		if (map->rays->dist_v < map->rays->dist_h)
		{
			map->rays->ray_x = map->rays->vert_x;
			map->rays->ray_y = map->rays->vert_y;
			map->rays->dist_h = map->rays->dist_v;
		}
		//draw_ray(map);
		// draw beam on screen
		lineH = ((TILE_RAD * 2) * HEIGHT) / (map->rays->dist_h);
		//if(lineH>320){ lineH=320;}
		draw_vert_line(map, lineH, 1, 160, i);
		map->rays->ray_angle = FixAng(map->rays->ray_angle - ray_int);
		map->rays->dof = 0;
		i++;
	}
	return (1);
}
