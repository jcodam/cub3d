/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:05:55 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/23 18:24:28 by avon-ben         ###   ########.fr       */
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

static void	rays_vertical(t_map *map, double Tan)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	map->rays->dist_v = 10000;
	if (map->rays->ray_angle == (0.5 * PI) \
	|| map->rays->ray_angle == (1.5 * PI))
	{
		set_straight_line(map, Tan);
		return ;
	}
	if (map->rays->ray_angle < (0.5 * PI) || map->rays->ray_angle > (1.5 * PI))
		vert_right(map, Tan);
	else if (map->rays->ray_angle > (0.5 * PI) \
	&& map->rays->ray_angle < (1.5 * PI))
		vert_left(map, Tan);
	while (!i)
		i = move_to_next_point_v(map, len++);
}

static void	rays_horizontal(t_map *map, double Tan)
{
	int	i;
	int	len;

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

int	cast_rays(t_map *map)
{
	double	tang;
	int		i;
	int		y_;

	i = 0;
	while (i < WIDTH)
	{
		map->rays->ray_angle = fixang(map->player.rot + atan((i - WIDTH / 2) \
		* (0.0174533 * FOV) / WIDTH));
		y_ = 0;
		tang = tan(map->rays->ray_angle);
		rays_vertical(map, tang);
		rays_horizontal(map, tang);
		if (map->rays->dist_v <= map->rays->dist_h)
			y_ = set_rays(map);
		draw_ray(map, 0);
		map->rays->dist_h = map->rays->dist_h * \
		cos(map->player.rot - map->rays->ray_angle);
		wall_texture(map, map->rays->dist_h, i++, y_);
	}
	return (1);
}
