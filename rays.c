/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:05:55 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/18 16:46:51 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
#include <stdlib.h>

//---------------------------Draw Rays and Walls--------------------------------

void	draw_line(t_map *map, double int_x, double int_y, int col)
{
	if (!col)
	{
		minimap_wrap_print(mini_x(map, map->rays->draw_x), \
		mini_y(map, map->rays->draw_y), map, ft_pixel(0, 0, 255, 200));
	}
	else
	{
		minimap_wrap_print(mini_x(map, map->rays->draw_x), \
		mini_y(map, map->rays->draw_y), map, ft_pixel(255, 0, 0, 200));
	}
	map->rays->draw_x += int_x;
	map->rays->draw_y += int_y;
	map->rays->dist_y -= int_y;
}

static void	draw_ray(t_map *map, int col)
{
	double	int_x;
	double	int_y;

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
				draw_line(map, int_x, int_y, col);
		}
		else if ((map->rays->dist_y < 0))
		{
			while (map->rays->dist_y < 0)
				draw_line(map, int_x, int_y, col);
		}
	}
}

int	move_to_next_point_h_down(t_map *map, int len)
{
	if (((int)map->rays->ray_x / TD) <= 0 || ((int)map->rays->ray_x / TD)
		>= (map->width) || ((int)map->rays->ray_y / TD) <= 0 || \
		((int)map->rays->ray_y / TD) >= (map->height) || \
		map->tiles[(int)((map->rays->ray_y / TD))]
		[(int)(map->rays->ray_x / TD)]->is_wall || len > 100)
	{
		map->rays->dist_h = cos(map->rays->ray_angle) * \
		(map->rays->ray_x - map->player.x_coor) - \
		sin(map->rays->ray_angle) * \
		(map->rays->ray_y - map->player.y_coor);
		return (1);
	}
	else
	{
		map->rays->ray_x += map->rays->offset_x;
		map->rays->ray_y += map->rays->offset_y;
		return (0);
	}
}

int	move_to_next_point_h_up(t_map *map, int len)
{
	if (((int)map->rays->ray_x / TD) <= 0 || ((int)map->rays->ray_x / TD) \
	>= (map->width) || ((int)map->rays->ray_y / TD) <= 0 || \
	((int)map->rays->ray_y / TD) >= (map->height) || \
	map->tiles[(((int)map->rays->ray_y) / TD)] \
	[((int)map->rays->ray_x / TD)]->is_wall || len > 100)
	{
		map->rays->dist_h = cos(map->rays->ray_angle) * \
		(map->rays->ray_x - map->player.x_coor) - \
		sin(map->rays->ray_angle) * \
		(map->rays->ray_y - map->player.y_coor);
		return (1);
	}
	else
	{
		map->rays->ray_x += map->rays->offset_x;
		map->rays->ray_y += map->rays->offset_y;
		return (0);
	}
}

int	move_to_next_point_h(t_map *map, int len)
{
	if (map->rays->ray_angle < (2 * PI) && map->rays->ray_angle > PI)
		return (move_to_next_point_h_up(map, len));
	if (map->rays->ray_angle > 0 && map->rays->ray_angle < PI)
		return (move_to_next_point_h_down(map, len));
	else
		return (0);
}

int	move_to_next_point_v(t_map *map, int len)
{
	if (((int)map->rays->vert_x / TD) <= 0 || ((int)map->rays->vert_x / TD) \
	>= (map->width) || ((int)map->rays->vert_y / TD) <= 0 || \
	((int)map->rays->vert_y / TD) >= (map->height) || \
	map->tiles[((int)map->rays->vert_y / TD)] \
	[((int)map->rays->vert_x / TD)]->is_wall || len > 100)
	{
		map->rays->dist_v = cos(map->rays->ray_angle) * \
		(map->rays->vert_x - map->player.x_coor) - \
		sin(map->rays->ray_angle) * \
		(map->rays->vert_y - map->player.y_coor);
		return (1);
	}
	else
	{
		map->rays->vert_x += map->rays->offset_x;
		map->rays->vert_y += map->rays->offset_y;
		return (0);
	}
}

void	get_distance_vert(t_map *map)
{
	while (((int)map->rays->vert_x / TD) > 0 && ((int)map->rays->vert_x / TD) \
	< (map->width) && !map->tiles[((int)map->rays->vert_y / TD)] \
	[((int)map->rays->vert_x / TD)]->is_wall)
		map->rays->vert_x += map->rays->offset_x;
	map->rays->dist_v = map->rays->vert_x - map->player.x_coor;
}

void	set_straight_line(t_map *map, double Tan)
{
	(void)Tan;
	if (map->rays->ray_angle == (0.5 * PI))
	{
		map->rays->offset_x = 0;
		map->rays->offset_y = TD;
	}
	else if (map->rays->ray_angle == PI)
	{
		map->rays->vert_x = (((int)map->player.x_coor / TD) * \
		TD) - 0.0001;
		map->rays->offset_x = -1 * TD;
		map->rays->offset_y = 0;
		get_distance_vert(map);
	}
	else if (map->rays->ray_angle == (1.5 * PI))
	{
		map->rays->offset_x = 0;
		map->rays->offset_y = -1 * TD;
	}
	else if (map->rays->ray_angle == (2 * PI))
	{
		map->rays->vert_x = (((int)map->player.x_coor / TD) * \
		TD + TD);
		map->rays->offset_x = TD;
		map->rays->offset_y = 0;
		get_distance_vert(map);
	}
}

void	vert_right(t_map *map, double Tan)
{
	map->rays->vert_x = (((int)map->player.x_coor / TD) * \
	TD + TD);
	map->rays->vert_y = (map->player.x_coor - map->rays->vert_x) * Tan + \
	map->player.y_coor;
	map->rays->offset_x = TD;
	map->rays->offset_y = (map->rays->offset_x * -1) * Tan;
}

void	vert_left(t_map *map, double Tan)
{
	map->rays->vert_x = (((int)map->player.x_coor / TD) * \
	TD) - 0.0001;
	map->rays->vert_y = (map->player.x_coor - map->rays->vert_x) * Tan + \
	map->player.y_coor;
	map->rays->offset_x = -1 * TD;
	map->rays->offset_y = (map->rays->offset_x * -1) * Tan;
}

void	hor_up(t_map *map, double Tan)
{
	map->rays->ray_y = (((int)map->player.y_coor / TD) * \
	TD) - 0.0001;
	map->rays->ray_x = (map->player.y_coor - map->rays->ray_y) * (1.0 / Tan) + \
	map->player.x_coor;
	map->rays->offset_y = -1 * TD;
	map->rays->offset_x = (-1 * map->rays->offset_y) * (1.0 / Tan);
}

void hor_down(t_map *map, double Tan)
{
	map->rays->ray_y = (((int)map->player.y_coor / TD) * \
	TD + TD);
	map->rays->ray_x = (map->player.y_coor - map->rays->ray_y) * (1.0 / Tan) + \
	map->player.x_coor;
	map->rays->offset_y = TD;
	map->rays->offset_x = (-1 * map->rays->offset_y) * (1.0 / Tan);
}

void rays_vertical(t_map *map, double Tan)
{
	int	i;
	int len;

	len = 0;
	i = 0;
	map->rays->dist_v = 10000;
	if (map->rays->ray_angle < (0.5 * PI) || map->rays->ray_angle > (1.5 * PI))
		vert_right(map, Tan);
	else if (map->rays->ray_angle > (0.5 * PI) \
	&& map->rays->ray_angle < (1.5 * PI))
		vert_left(map, Tan);
	else
	{
		set_straight_line(map, Tan);
		return ;
	}
	while (!i)
		i = move_to_next_point_v(map, len++);
}

void rays_horizontal(t_map *map, double Tan)
{
	int	i;
	int len;

	len = 0;
	i = 0;
	map->rays->dist_h = 10000;
	if (map->rays->ray_angle > 0.0 && map->rays->ray_angle < PI)
		hor_up(map, Tan);
	else if (map->rays->ray_angle > PI && map->rays->ray_angle < (2 * PI))
		hor_down(map, Tan);
	else
	{
		set_straight_line(map, Tan);
		return ;
	}
	while (!i)
		i = move_to_next_point_h(map, len++);
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

void offset_cosine(t_map *map)
{
	
}

int	cast_rays(t_map *map)
{
	double	tang;
	int		i;
	int		y_;
	double	line_int;

	i = 0;
	line_int = (((FOV * 1.0) / PI) / WIDTH);
	map->rays->ray_angle = map->player.rot + (((FOV * 1.0) / PI) / 2);
	while (i < WIDTH)
	{
		map->rays->ray_angle = FixAng(map->rays->ray_angle - line_int);
		y_ = 0;
		tang = tan(map->rays->ray_angle);
		rays_vertical(map, tang);
		rays_horizontal(map, tang);
		if (map->rays->dist_v <= map->rays->dist_h)
		{
			map->rays->ray_x = map->rays->vert_x;
			map->rays->ray_y = map->rays->vert_y;
			map->rays->dist_h = map->rays->dist_v;
			y_ = 1;
		}
		draw_ray(map, 0);
		//offset_cosine(map);
		//map->rays->dist_h = map->rays->dist_h * cos(map->rays->ray_angle);
		//wall_texture(map, map->rays->dist_h, i++, y_);
		i++;
	}
	return (1);
}
