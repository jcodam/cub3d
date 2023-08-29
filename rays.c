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

static void	draw_ray(t_map *map)
{
	float	int_x;
	float	int_y;
	float	dist_x;
	float	dist_y;
	float	draw_x;
	float	draw_y;

	draw_x = map->player.x_coor;
	draw_y = map->player.y_coor;
	dist_x = (map->rays->ray_x - map->player.x_coor);
	dist_y = (map->rays->ray_y - map->player.y_coor);
	int_x = dist_x / 100;
	int_y = dist_y / 100;
	// printf("dist_x: %f\n", dist_x);
	// printf("dist_y: %f\n", dist_y);
	if (dist_x == 0 || dist_y == 0)
		return ;
	if (map->rays->dist_H <= map->rays->dist_H)
	{
		if (dist_y > 0)
		{
			while (dist_y > 0)
			{
				//exit(0);
				minimap_wrap_print(mini_x(map, draw_x), mini_y(map, draw_y), map, \
				ft_pixel(0, 0, 255, 200));
				draw_x += int_x;
				draw_y += int_y;
				dist_y -= int_y;
			}
		}
		else if ((dist_y < 0))
		{
			while (dist_y < 0)
			{
				minimap_wrap_print(mini_x(map, draw_x), mini_y(map, draw_y), map, \
				ft_pixel(0, 0, 255, 200));
				draw_x += int_x;
				draw_y += int_y;
				dist_y -= int_y;
			}
		}
	}
	else
	{
		if (dist_x > 0)
		{
			while (dist_x > 0)
			{
				minimap_wrap_print(mini_x(map, draw_x), mini_y(map, draw_y), map, \
				ft_pixel(0, 0, 255, 200));
				draw_x += int_x;
				draw_y += int_y;
				dist_x -= int_x;
			}
		}
		else if (dist_x < 0)
		{
			while (dist_x < 0)
			{
				minimap_wrap_print(mini_x(map, draw_x), mini_y(map, draw_y), map, \
				ft_pixel(0, 0, 255, 200));
				draw_x += int_x;
				draw_y += int_y;
				dist_x -= int_x;
			}
		}
	}
}

int	rays_hor(t_map *map)
{
	float	ray_y;
	float	ray_x;
	float	y_offset;
	float	x_offset;
	float	Tan;
	int 	ray_angle;
	int		i;
	float	vert_x;
	float	vert_y;

	i = 0;
	ray_angle = map->player.rotation + FOV;
	while (i < (FOV * 2))
	{
		map->rays->dof = 0;
		Tan = tan((degToRad(ray_angle)));
		map->rays->dist_V = 100000;
		// Vertical
		if (ray_angle < 90 || ray_angle > 270)
		{ //right
			ray_x = (((int)map->player.x_coor / (2 * TILE_RAD)) * \
			(2 * TILE_RAD) + (2 * TILE_RAD));
			ray_y = (map->player.x_coor - ray_x) * Tan + map->player.y_coor;
			x_offset = (2 * TILE_RAD);
			y_offset = (x_offset * -1) * Tan;
		}
		else if (ray_angle > 90 && ray_angle < 270)
		{ // left
			ray_x = (((int)map->player.x_coor / (2 * TILE_RAD)) * \
			(2 * TILE_RAD)) - 0.0001;
			ray_y = (map->player.x_coor - ray_x) * Tan + map->player.y_coor;
			x_offset = -1 * (2 * TILE_RAD);
			y_offset = (x_offset * -1) * Tan;
		}
		else
		{
			ray_x = map->player.x_coor;
			ray_y = map->player.y_coor;
			map->rays->dof = 8;
		}
		while (map->rays->dof < 8)
		{
			if (((int)ray_x / 64) <= 0 || ((int)ray_x / 64) >= (map->width) \
			|| ((int)ray_y / 64) <= 0 || ((int)ray_y / 64) >= (map->height) \
			|| map->tiles[((int)ray_y / 64)][((int)ray_x / 64)]->is_wall)
			{
				map->rays->dof = 8;
				map->rays->dist_V = cos(degToRad(ray_angle)) * (ray_x \
				- map->player.x_coor) - sin(degToRad(ray_angle)) * \
				(ray_y - map->player.y_coor);
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				map->rays->dof++;
			}
		}
		printf("ray_x vert: %d\n", ((int)ray_x / 64));
		printf("ray_y vert: %d\n", ((int)ray_y / 64));
		vert_x = ray_x;
		vert_y = ray_y;
		map->rays->dof = 0;
		map->rays->dist_H = 100000;
		// Horizontal
		if (sin(degToRad(ray_angle)) > 0.00001)
		{ //up
			ray_y = (((int)map->player.y_coor / (2 * TILE_RAD)) * (2 * TILE_RAD) - 0.001);
			ray_x = (map->player.y_coor - ray_y) * (1.0 / Tan) + map->player.x_coor;
			y_offset = -1 * (2 * TILE_RAD);
			x_offset = (-1 * y_offset) * (1.0 / Tan);
		}
		else if (sin(degToRad(ray_angle)) < 0.00001)
		{ // down
			ray_y = (((int)map->player.y_coor / (2 * TILE_RAD)) * (2 * TILE_RAD) + (2 * TILE_RAD));
			ray_x = (map->player.y_coor - ray_y) * (1.0 / Tan) + map->player.x_coor;
			y_offset = (2 * TILE_RAD);
			x_offset = (-1 * y_offset) * (1.0 / Tan);
		}
		else
		{
			ray_x = map->player.x_coor;
			ray_y = map->player.y_coor;
			map->rays->dof = 8;
		}
		while (map->rays->dof < 8)
		{
			if (((int)ray_x / (2 * TILE_RAD)) <= 0 || ((int)ray_x / (2 * TILE_RAD)) >= (map->width) \
			|| ((int)ray_y / (2 * TILE_RAD)) <= 0 || ((int)ray_y / (2 * TILE_RAD)) >= (map->height) \
			|| map->tiles[((int)ray_y / (2 * TILE_RAD))][((int)ray_x / (2 * TILE_RAD))]->is_wall)
			{
				map->rays->dof = 8;
				map->rays->dist_H = cos(degToRad(ray_angle)) * (ray_x \
				- map->player.x_coor) - sin(degToRad(ray_angle)) * \
				(ray_y - map->player.y_coor);
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				map->rays->dof++;
			}
		}
		// printf("ray_x hor: %d\n", ((int)ray_x / 64));
		// printf("ray_y hor: %d\n", ((int)ray_y / 64));
		// printf ("dist_v: %f\n", map->rays->dist_V);
		// printf ("dist_h: %f\n", map->rays->dist_H);
		if (map->rays->dist_V < map->rays->dist_H)
		{
			ray_x = vert_x;
			ray_y = vert_y;
			map->rays->dist_H = map->rays->dist_V;
		}
		map->rays->ray_x = ray_x;
		map->rays->ray_y = ray_y;
		map->rays->offset_x = x_offset;
		map->rays->offset_y = y_offset;
		draw_ray(map);
		i++;
		ray_angle = FixAng(ray_angle - 1);
	}
	return (1);
}

void	draw_rays(t_map *map)
{
	int		side;

	map->rays->dof = 0;
	side = 0;
	rays_hor(map);
	//rays_ver(map);
}
