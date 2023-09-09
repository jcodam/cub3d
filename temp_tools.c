/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:20:17 by jbax              #+#    #+#             */
/*   Updated: 2023/09/09 16:20:18 by jbax             ###   ########.fr       */
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
			printf("tile x: %d, tile y: %d\n", map->tiles[i][j]->x, \
			map->tiles[i][j]->y);
			printf("is wall: %d\n\n", map->tiles[i][j]->is_wall);
			j++;
		}
		j = 0;
		i++;
	}
}
