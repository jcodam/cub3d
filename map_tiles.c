/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:07:48 by jbax              #+#    #+#             */
/*   Updated: 2023/10/23 18:34:21 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "map.h"
#include "defines.h"

static size_t	get_map_height(char **map_arr)
{
	size_t	i;

	if (!map_arr)
		map_exit("test");
	i = 0;
	while (map_arr[i])
		i++;
	return (i);
}

static size_t	get_map_width(char **map_arr)
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
	init_tile_part(tile, i, j);
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

t_tile	***init_tiles(t_map *map, size_t j, size_t width, t_tile ***tiles)
{
	int	i;

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
	return (tiles);
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
	map->tiles = init_tiles(map, j, width, tiles);
	return (1);
}
