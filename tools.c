/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:01:18 by avon-ben          #+#    #+#             */
/*   Updated: 2023/09/11 13:07:23 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"

float	get_mmap_centre_x(void)
{
	return (((MAX_X_MINIMAP - MIN_X_MINIMAP) / 2) + MIN_X_MINIMAP);
}

float	get_mmap_centre_y(void)
{
	return (((MAX_Y_MINIMAP - MIN_Y_MINIMAP) / 2) + MIN_Y_MINIMAP);
}

float	mini_rel_x(t_map *map, int i, int j)
{
	return (map->tiles[i][j]->rel_x + get_mmap_centre_x());
}

float	mini_rel_y(t_map *map, int i, int j)
{
	return (map->tiles[i][j]->rel_y + get_mmap_centre_y());
}

uint32_t	mini_x(t_map *map, float x)
{
	float	rel;

	rel = x - map->player.x_coor;
	return (rel + get_mmap_centre_x());
}

uint32_t	mini_y(t_map *map, float y)
{
	float	rel;

	rel = y - map->player.y_coor;
	return (rel + get_mmap_centre_y());
}
