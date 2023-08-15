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

// // float	distance(float ax, float ay, float bx, float by, float ang)
// // {
// // 	return (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));
// // }

void	check_up_down_vert(t_map *map,float Tan)
{
	if (cos(degToRad(map->player.rotation)) > 0.001)
	{
		map->rays->ray_x = (((int)map->player.x_coor >> 6) << 6) + 64;
		map->rays->ray_y = (map->player.x_coor - map->rays->ray_x) * Tan \
		+ map->player.y_coor;
		map->rays->offset_x = 64;
		map->rays->offset_y = -map->rays->offset_x * Tan;
	}
	else if (cos(degToRad(map->player.rotation)) < -0.001)
	{
		map->rays->ray_x = (((int)map->player.x_coor >> 6) << 6) - 0.0001;
		map->rays->ray_y = (map->player.x_coor - map->rays->ray_x) * Tan \
		+ map->player.y_coor;
		map->rays->offset_x = -64;
		map->rays->offset_y = -map->rays->offset_x * Tan;
	}
	else
	{
		map->rays->ray_x = map->player.x_coor;
		map->rays->ray_y = map->player.y_coor;
		map->rays->dof = 8;
	}
}

void	make_vector_vert(t_map *map)
{
	int	map_x;
	int	map_y;

	while (map->rays->dof < 8)
	{
	map_x = (int)(map->rays->ray_x) >> 6;
	map_y = (int)(map->rays->ray_y) >> 6;
		if (map_x > 0 && map_y > 0 && map_x < map->width && map_y < map->height \
		&& !map->tiles[map_x][map_y]->is_open)
		{
			map->rays->dof = 8;
			map->rays->dist_V = cos(degToRad(map->player.rotation)) * \
			(map->rays->ray_x - map->player.x_coor) - \
			sin(degToRad(map->player.rotation)) * (map->rays->ray_y - \
			map->player.y_coor);
		}
		else
		{
			map->rays->ray_x += map->rays->offset_x;
			map->rays->ray_y += map->rays->offset_x;
			map->rays->dof += 1;
		}
	}
	map->rays->vector_x = map->rays->ray_x;
	map->rays->vector_y = map->rays->ray_y;
}

void draw_rays(t_map *map)
{
	int		raynum;
	int		side;
	float	Tan;

	raynum = 0;
	// check Tan vs invTan
	Tan = tan(degToRad(map->player.rotation));
	map->rays->dof = 0;
	side = 0;
	map->rays->dist_V = 100000;
	check_up_down_vert(map, Tan);
	make_vector_vert(map);
}
