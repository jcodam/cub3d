/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:42:39 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/23 18:38:42 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
#include <stdlib.h>

int	move_to_next_point_h(t_map *map, int len)
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

void	set_straight_line(t_map *map, double Tan)
{
	(void)Tan;
	map->rays->offset_x = 0;
	if (map->rays->ray_angle == (0.5 * PI))
		map->rays->offset_y = -1 * TD;
	else if (map->rays->ray_angle == (1.5 * PI))
		map->rays->offset_y = TD;
}

int	set_rays(t_map *map)
{
	map->rays->ray_x = map->rays->vert_x;
	map->rays->ray_y = map->rays->vert_y;
	map->rays->dist_h = map->rays->dist_v;
	return (1);
}
