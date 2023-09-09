/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:32 by jbax              #+#    #+#             */
/*   Updated: 2023/09/09 17:11:21 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
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
	tile->height = TILE_HEIGHT;
	tile->is_player = 0;
	tile->is_wall = 0;
	if (!map->map_arr[i][j] || !ft_strchr("ENSW10", map->map_arr[i][j]))
		tile->not_map = 1;
	if (ft_strchr("ENSW", map->map_arr[i][j]))
	{
		tile->is_player = 1;
	}
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
	i = 0;
	j = 0;
	if (!map)
		return (0);
	tiles = malloc(sizeof(t_tile **) * (height + 1));
	tiles[height] = NULL;
	if (!tiles)
		return (0);
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
		j = 0;
		i++;
	}
	map->tiles = tiles;
	return (1);
}

void	start_mapping(char *addr)
{
	t_map	*map;

	map = mk_map();
	fill_map(map, addr);
	if (!make_tiles(map))
		exit(1);
	prep_map_syntax(map);
	check_map(map);
	mk_png(map);
	draw_map(map);
	map = del_png_s(map);
	map = del_map(map);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		ft_putnbr_fd(argc, 1);
		ft_putendl_fd(FG_RED"Error\nyou forgot map input"FG_DEFAULT, 1);
		return (1);
	}
	fg_putstr_rgb_fd(argv[1], "45;255;45", 1);
	write(1, "\n", 1);
	_cub(argv[1]);
	start_mapping(argv[1]);
	return (0);
}
