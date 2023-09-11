/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:05:55 by avon-ben          #+#    #+#             */
/*   Updated: 2023/09/11 13:10:43 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
#include <stdlib.h>

//---------------------------Draw Rays and Walls--------------------------------

void	draw_line(t_map *map, float int_x, float int_y)
{
	minimap_wrap_print(mini_x(map, map->rays->draw_x), \
	mini_y(map, map->rays->draw_y), map, ft_pixel(0, 0, 255, 200));
	map->rays->draw_x += int_x;
	map->rays->draw_y += int_y;
	map->rays->dist_y -= int_y;
}

static void	draw_ray(t_map *map)
{
	float	int_x;
	float	int_y;

	map->rays->draw_x = map->player.x_coor;
	map->rays->draw_y = map->player.y_coor;
	map->rays->dist_x = (map->rays->ray_x - map->player.x_coor);
	map->rays->dist_y = (map->rays->ray_y - map->player.y_coor);
	int_x = map->rays->dist_x / 100;
	int_y = map->rays->dist_y / 100;
	if (map->rays->dist_h <= map->rays->dist_h)
	{
		if (map->rays->dist_y > 0)
		{
			while (map->rays->dist_y > 0)
				draw_line(map, int_x, int_y);
		}
		else if ((map->rays->dist_y < 0))
		{
			while (map->rays->dist_y < 0)
				draw_line(map, int_x, int_y);
		}
	}
}

void	move_to_next_point_h(t_map *map)
{
	if (((int)map->rays->ray_x / 64) <= 0 || ((int)map->rays->ray_x / 64) \
	>= (map->width) || ((int)map->rays->ray_y / 64) <= 0 || \
	((int)map->rays->ray_y / 64) >= (map->height) || \
	map->tiles[((int)map->rays->ray_y / 64)] \
	[((int)map->rays->ray_x / 64)]->is_wall)
	{
		map->rays->dof = 20;
		map->rays->dist_h = cos(degree_to_radian(map->rays->ray_angle)) * \
		(map->rays->ray_x - map->player.x_coor) - \
		sin(degree_to_radian(map->rays->ray_angle)) * \
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
		map->rays->dof = 20;
		map->rays->dist_v = cos(degree_to_radian(map->rays->ray_angle)) * \
		(map->rays->vert_x - map->player.x_coor) - \
		sin(degree_to_radian(map->rays->ray_angle)) * \
		(map->rays->vert_y - map->player.y_coor);
	}
	else
	{
		map->rays->vert_x += map->rays->offset_x;
		map->rays->vert_y += map->rays->offset_y;
		map->rays->dof++;
	}
}

void	get_distance_vert(t_map *map)
{
	while(((int)map->rays->vert_x / 64) > 0 && ((int)map->rays->vert_x \
	/ 64) < (map->width) && !map->tiles[((int)map->rays->vert_y / 64)] \
	[((int)map->rays->vert_x / 64)]->is_wall)
		map->rays->vert_x += map->rays->offset_x;
	map->rays->dist_v = map->rays->vert_x - map->player.x_coor;
}

void	set_streight_line(t_map *map, float Tan)
{
	(void)Tan;
	if (map->rays->ray_angle == 90)
	{
		map->rays->offset_x = 0;
		map->rays->offset_y = (2 * TILE_RAD);
	}
	else if (map->rays->ray_angle > 179.75 && map->rays->ray_angle < 180.25)
	{
		map->rays->vert_x = (((int)map->player.x_coor / (2 * TILE_RAD)) * \
		(2 * TILE_RAD)) - 0.0001;
		map->rays->offset_x = -1 * (2 * TILE_RAD);
		map->rays->offset_y = 0;
		get_distance_vert(map);
	}
	else if (map->rays->ray_angle == 270)
	{
		map->rays->offset_x = 0;
		map->rays->offset_y = -1 * (2 * TILE_RAD);
	}
	else if (map->rays->ray_angle > 359.75 && map->rays->ray_angle < 0.25)
	{
		map->rays->vert_x = (((int)map->player.x_coor / (2 * TILE_RAD)) * \
		(2 * TILE_RAD) + (2 * TILE_RAD));
		map->rays->offset_x = (2 * TILE_RAD);
		map->rays->offset_y = 0;
		get_distance_vert(map);
	}
	map->rays->dof = 20;
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
		set_streight_line(map, Tan);
	while (map->rays->dof < 20)
		move_to_next_point_v(map);
}

void rays_horizontal(t_map *map, float Tan)
{
	map->rays->dist_h = 100000;
	map->rays->dof = 0;
	if (map->rays->ray_angle > 0 && map->rays->ray_angle < 180)
		hor_up(map, Tan);
	else if (map->rays->ray_angle > 180 && map->rays->ray_angle < 360)
		hor_down(map, Tan);
	else
	{
		set_streight_line(map, Tan);
		return ;
	}
	while (map->rays->dof < 20)
		move_to_next_point_h(map);
}

void draw_vert_line(t_map *map, int height, int width, int start_y, int pos)
{
	int	x;
	int	y;
	int	start_x;

	x = pos;
	start_x = x;
	y = start_y;
	while (x < (start_x + width) && x < WIDTH)
	{
		while (y < height)
		{
			put_pixel_wrap(map->mini, x, y, ft_pixel(0, 255, 0, 150));
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
	int		y_;
	float	line_int;

	line_int = ((FOV * 1.0) / WIDTH);
	i = 0;
	map->rays->ray_angle = map->player.rotation + (FOV / 2);
	while (i < WIDTH)
	{
		map->rays->ray_angle = FixAng(map->rays->ray_angle - line_int);
		y_ = 0;
		tang = tan((degree_to_radian(map->rays->ray_angle)));
		rays_vertical(map, tang);
		rays_horizontal(map, tang);
		if (map->rays->dist_v <= map->rays->dist_h)
		{
			map->rays->ray_x = map->rays->vert_x;
			map->rays->ray_y = map->rays->vert_y;
			map->rays->dist_h = map->rays->dist_v;
			y_ = 1;
		}
		draw_ray(map);
		i++;
		wall_texture(map, map->rays->dist_h, i, y_);
		map->rays->dof = 0;
	}
	return (1);
}
