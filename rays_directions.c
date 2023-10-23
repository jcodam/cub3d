/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:42:48 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/23 18:38:28 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
#include <stdlib.h>

void	vert_right(t_map *map, double Tan)
{
	map->rays->vert_x = ((int)(map->player.x_coor / TD) * \
	TD + TD);
	map->rays->vert_y = (map->player.x_coor - map->rays->vert_x) * Tan + \
	map->player.y_coor;
	map->rays->offset_x = TD;
	map->rays->offset_y = (map->rays->offset_x * -1) * Tan;
}

void	vert_left(t_map *map, double Tan)
{
	map->rays->vert_x = ((int)(map->player.x_coor / TD) * \
	TD) - 0.0001;
	map->rays->vert_y = (map->player.x_coor - map->rays->vert_x) * Tan + \
	map->player.y_coor;
	map->rays->offset_x = -1 * TD;
	map->rays->offset_y = (map->rays->offset_x * -1) * Tan;
}

void	hor_up(t_map *map, double Tan)
{
	map->rays->ray_y = ((int)(map->player.y_coor / TD) * \
	TD) - 0.0001;
	map->rays->ray_x = (map->player.y_coor - map->rays->ray_y) * (1.0 / Tan) + \
	map->player.x_coor;
	map->rays->offset_y = -1 * TD;
	map->rays->offset_x = (-1 * map->rays->offset_y) * (1.0 / Tan);
}

void	hor_down(t_map *map, double Tan)
{
	map->rays->ray_y = ((int)(map->player.y_coor / TD) * \
	TD) + TD;
	map->rays->ray_x = (map->player.y_coor - map->rays->ray_y) * (1.0 / Tan) + \
	map->player.x_coor;
	map->rays->offset_y = TD;
	map->rays->offset_x = (-1 * map->rays->offset_y) * (1.0 / Tan);
}
