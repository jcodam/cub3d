/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:20:17 by jbax              #+#    #+#             */
/*   Updated: 2023/10/18 17:40:58 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"
#include "stdio.h"

void	print_tiles(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			// printf("\n\ni: %d, j: %d\n",i, j);
			// printf("tile x: %d, tile y: %d\n", map->tiles[i][j]->x, \
			// map->tiles[i][j]->y);
			// printf("is wall: %d\n", map->tiles[i][j]->is_wall);
			// printf("not map: %d\n", map->tiles[i][j]->not_map);
			// printf("x_coor: %f, y_coor: %f\n", map->tiles[i][j]->x_coor, map->tiles[i][j]->y_coor);
			// printf("rel_x: %f, rel_y: %f\n", map->tiles[i][j]->rel_x, map->tiles[i][j]->rel_y);
			// printf("rel_x conv: %d, rel_y conv: %d\n", ((int)map->tiles[i][j]->rel_x) / 64, (int)map->tiles[i][j]->rel_y / 64);
			// printf("height: %d, width: %d\n\n", map->height, map->width);
			j++;
		}
		j = 0;
		i++;
	}
}
