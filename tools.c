/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:01:18 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/12 19:45:41 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"

double	get_mmap_centre_x(void)
{
	return (((MAX_X_MINIMAP - MIN_X_MINIMAP) / 2) + MIN_X_MINIMAP);
}

double	get_mmap_centre_y(void)
{
	return (((MAX_Y_MINIMAP - MIN_Y_MINIMAP) / 2) + MIN_Y_MINIMAP);
}

double	mini_rel_x(t_map *map, int i, int j)
{
	return (map->tiles[i][j]->rel_x + get_mmap_centre_x());
}

double	mini_rel_y(t_map *map, int i, int j)
{
	return (map->tiles[i][j]->rel_y + get_mmap_centre_y());
}

uint32_t	mini_x(t_map *map, double x)
{
	double	rel;

	rel = x - map->player.x_coor;
	return (rel + get_mmap_centre_x());
}
