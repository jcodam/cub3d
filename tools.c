/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 19:01:18 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/08/13 18:16:27 by avon-ben      ########   odam.nl         */
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

int	mini_x(float x)
{
	return (x + MIN_X_MINIMAP);
}

int	mini_y(float y)
{
	return (y + MIN_Y_MINIMAP);
}
