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

// float	distance(float ax, float ay, float bx, float by, float ang)
// {
// 	return (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));
// }

// static void	check_up_down_vert(t_map *map)
// {
// 	if (cos(degToRad(map->player.rotation)) > 0.001)
// 	{
// 		map->rays->ray_x = (((int)map->player.x_coor >> 6) << 6) + 64;
// 		printf("ray_x: %f", map->rays->ray_x);
// 		printf("ray_y: %f", map->rays->ray_y);
// 		map->rays->ray_y = (map->player.x_coor - map->rays->ray_x) * Tan \
// 		+ map->player.y_coor;
// 		map->rays->offset_x = TILE_RAD * 2;
// 		map->rays->offset_y = -map->rays->offset_x * Tan;
// 	}
// 	if (cos(degToRad(map->player.rotation)) < -0.001)
// 	{
// 		map->rays->ray_x = (((int)map->player.x_coor >> 6) << 6) - 0.0001;
// 		map->rays->ray_y = (map->player.x_coor - map->rays->ray_x) * Tan \
// 		+ map->player.y_coor;
// 		map->rays->offset_x = -64;
// 		map->rays->offset_y = -map->rays->offset_x * Tan;
// 	}
// 	else
// 	{
// 		map->rays->ray_x = map->player.x_coor;
// 		map->rays->ray_y = map->player.y_coor;
// 		map->rays->dof = 8;
// 	}
// }

float set_streight_lr(t_map *map)
{
	float int_x;

	printf("ray_x: %f, player x_coor: %f", map->rays->ray_x, map->player.x_coor);
	if (map->rays->ray_x == map->player.x_coor)
	{
		printf("streight left or right\n");
		int_x = 1;
	}
	if (!map->player.rotation)
		int_x *= -1;
	else
		int_x = map->rays->ray_x - map->player.x_coor;
	return (int_x);
}

float set_inty_ud(t_map *map)
{
	float int_y;

	printf("ray_y: %f, player y_coor: %f", map->rays->ray_y, map->player.y_coor);
	if (map->rays->ray_y == map->player.y_coor)
	{
		printf("streight up or down\n");
		int_y = 1;
	}
	if (map->player.rotation == 90)
		int_y *= -1;
	else
		int_y = map->rays->ray_y - map->player.y_coor;
	return (int_y);
}

static void	draw_ray(t_map *map)
{
	// float	int_x;
	// float	int_y;
	float	draw_x;
	float	draw_y;

	draw_x = map->player.x_coor;
	draw_y = map->player.y_coor;
	printf("draw_x: %f, draw_y: %f\n", draw_x, draw_y);
	//printf("vector_x: %f, vector_y: %f\n", map->rays->vector_x, map->rays->vector_y);
	printf("ray_x: %f, ray_y: %f\n", map->rays->ray_x, map->rays->ray_y);
	printf("offset_x: %f, offset_y: %f\n", map->rays->offset_x, map->rays->offset_y);
	printf("dist_v: %f, dist_h: %f\n", map->rays->dist_V, map->rays->dist_H);
	printf("x_angle: %f, y_angle: %f", map->player.x_angle, map->player.y_angle);
	printf("dof: %d", map->rays->dof);
	// exit(0);
}
// 	// fix this!! 
// 	if (map->rays->ray_x == map->player.x_coor)
// 	{
// 		int_x = 0;
// 	}
// 	else
// 		int_x = map->rays->ray_x - map->player.x_coor;
// 	int_y = set_inty_ud(map);
// 	if (map->rays->ray_y == map->player.y_coor)
// 	{
// 		int_y = 0;
// 	}
// 	else
// 		int_y = map->rays->ray_y - map->player.y_coor;
// 	int_x = set_streight_lr(map);
// 	printf("int_x: %f, int_y: %f\n", int_x, int_y);
// 	printf("offset_x: %f, offset_y: %f\n", map->rays->offset_x, map->rays->offset_y);
// 	while (map->rays->dist_V) //&& map->rays->dist_H)
// 	{
// 		put_pixel_wrap(map->img, (uint32_t)mini_x(draw_x), (uint32_t)mini_y(draw_y), \
// 		ft_pixel(0, 255, 10, 200));
// 		draw_x += (int_x / 100);
// 		draw_y += (int_y / 100);
// 		map->rays->dist_V -= int_y / 100;
// 		map->rays->dist_H -= int_x / 100;
// 	}
// }

int rays_hor(t_map *map)
{
	float aTan = -1/tan(degToRad(map->player.rotation));
	float ray_y;
	float ray_x;
	float y_offset;
	float x_offset;

	if (degToRad(map->player.rotation) > PI)
	{ //down
		ray_y = (((int)map->player.y_coor / (2 * TILE_RAD)) * (2 * TILE_RAD));
		ray_x = (map->player.y_coor - ray_y) * aTan + map->player.x_coor;
		y_offset = (2 * TILE_RAD);
		x_offset = y_offset * aTan;
	}
	else if (degToRad(map->player.rotation) < PI)
	{ // up
		ray_y = (((int)map->player.y_coor / (2 * TILE_RAD)) * (2 * TILE_RAD)) + (2 * TILE_RAD);
		ray_x = (map->player.y_coor - ray_y) * aTan + map->player.x_coor;
		y_offset = -1 * (2 * TILE_RAD);
		x_offset = y_offset * aTan;
	}
	else if (degToRad(map->player.rotation) == 0 || degToRad(map->player.rotation) == PI)
	{
		ray_x = map->player.x_coor;
		ray_y = map->player.y_coor;
		map->rays->dof = 8;
	}
	while(map->rays->dof < 8 && ray_x < HEIGHT && ray_x > 0 && ray_y < WIDTH && ray_y > 0)
	{
		//printf("map_arr[%d][%d]: %c\n", ((int)ray_y / 64) + 1,  ((int)ray_x / 64), map->map_arr[(((int)ray_y / 64) + 1)][((int)ray_x / 64)]);
		if(!map->tiles[((int)ray_y / 64) + 1][(int)ray_x / 64]->is_open)
		{
			map->rays->dof = 8;
			map->rays->dist_V=cos(degToRad(map->player.rotation)) * (map->rays->ray_x - map->player.x_coor)-sin(degToRad(map->player.rotation))*(map->rays->ray_y - map->player.x_coor);
		}
		else
		{
			ray_x += x_offset;
			ray_y += y_offset;
			map->rays->dof++;
		}
	}
	map->rays->ray_x = ray_x;
	map->rays->ray_y = ray_y;
	map->rays->offset_x = x_offset; 
	map->rays->offset_y = y_offset;
	//printf("player_x: %f, player_y: %f, ray_x: %f. ray_y: %f\n", map->player.x_coor, map->player.y_coor, ray_x, ray_y);
	draw_ray(map);
	return (1);
}

void draw_rays(t_map *map)
{
	int		raynum;
	int		side;

	raynum = 0;
	map->rays->dof = 0;
	side = 0;
	map->rays->dist_V = 100000;
	rays_hor(map);
}
