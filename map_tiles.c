/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:07:48 by jbax              #+#    #+#             */
/*   Updated: 2023/10/11 10:52:56 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "map.h"
#include "defines.h"

int	get_map_height(char **map_arr)
{
	int	i;

	if (!map_arr)
		map_exit("test");
	i = 0;
	while (map_arr[i])
		i++;
	return (i);
}

size_t	get_map_width(char **map_arr)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (map_arr[i])
	{
		if ((ft_strlen(map_arr[i]) > len))
			len = ft_strlen(map_arr[i]);
		i++;
	}
	return (len);
}

t_tile	*init_tile(size_t i, size_t j, t_map *map)
{
	t_tile	*tile;

	tile = malloc(sizeof(t_tile));
	if (!tile)
		exit (0);
	if (j > ft_strlen(map->map_arr[i]))
	{
		tile->not_map = 1;
		return (tile);
	}
	tile->x = j;
	tile->y = i;
	tile->x_coor = tile->x * (TILE_RAD * 2);
	tile->y_coor = tile->y * (TILE_RAD * 2);
	tile->not_map = 0;
	tile->is_player = 0;
	tile->is_wall = 0;
	if (!map->map_arr[i][j] || !ft_strchr("ENSW10", map->map_arr[i][j]))
		tile->not_map = 1;
	if (ft_strchr("ENSW", map->map_arr[i][j]))
		tile->is_player = 1;
	if (map->map_arr[i][j] == '1')
		tile->is_wall = 1;
	map->height = get_map_height(map->map_arr);
	map->width = get_map_width(map->map_arr);
	return (tile);
}

int	make_tiles(t_map *map)
{
	size_t	i;
	size_t	j;
	t_tile	***tiles;
	size_t	width;
	size_t	height;

	height = get_map_height(map->map_arr);
	width = get_map_width(map->map_arr);
	printf("width: %ld, height: %ld\n", width, height);
	i = 0;
	j = 0;
	if (!map)
		return (0);
	tiles = malloc(sizeof(t_tile **) * (height + 1));
	if (!tiles)
		return (0);
	tiles[height] = NULL;
	while (i < height)
	{
		tiles[i] = malloc(sizeof(t_tile *) * (width + 1));
		if (!tiles[i])
			return (0);
		i++;
	}
	i = 0;
	while (tiles[i])
	{
		while (j < width)
		{
			tiles[i][j] = init_tile(i, j, map);
			j++;
		}
		tiles[i][width] = NULL;
		j = 0;
		i++;
	}
	map->tiles = tiles;
	return (1);
}