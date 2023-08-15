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

// #include "map.h"
// #include "defines.h"

// // float	distance(float ax, float ay, float bx, float by, float ang)
// // {
// // 	return (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));
// // }

check_up_down_vert(t_map *map, int side, int disV, float invTan)
{
	if (cos(degToRad(map->player.rotation)) > 0.001)
	{
		map->rays->ray_x = (((int)map->player.x_coor >> 6) << 6) + 64;
		map->rays->ray_y = (map->player.x_coor - map->rays->ray_x) * invTan + map->player.y_coor;
		map->rays->offset_x = 64;
		map->rays->offset_y = -map->rays->offset_x * invTan;
	}
	else if (cos(degToRad(map->player.rotation)) < -0.001)
	{
		map->rays->ray_x = (((int)map->player.x_coor >> 6) << 6) - 0.0001;
		map->rays->ray_y = (map->player.x_coor - map->rays->ray_x) * invTan + map->player.y_coor;
		map->rays->offset_x = -64;
		map->rays->offset_y = -map->rays->offset_x * invTan;
	}
	else
	{
		map->rays->ray_x = map->player.x_coor;
		map->rays->ray_y = map->player.y_coor;
		map->rays->dof = 8;
	}
}

void make_vector_map(t_map *map)
{
	while (map->rays->dof < 8)
	{
	mx = (int)(map->rays->ray_x) >> 6;
	my = (int)(ray_y) >> 6;
	mp = my * mapX + mx;
		if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
		{
			dof = 8;
			disV = cos(degToRad(r_rot)) * (ray_x - map->player.x_coor) \
			- sin(degToRad(r_rot)) * (ray_y - map->player.y_coor);
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	vx = map->rays->ray_x; 
	vy = ray_y;

	
// }


void draw_rays(t_map *map)
{
	float	invTan;
	int		raynum;
	int		offset_x;
	int		offset_y;
	int		side;
	int		disV;

	raynum = 0;
	// check Tan vs invTan	
	invTan - -1 / tan(map->player.rotation);
	map->rays->dof = 0;
	side = 0;
	disV = 100000;
	check_up_down_vert(map, side, disV, invTan);
	make_vector_vert(map);
	
}
