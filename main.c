/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:07:32 by jbax          #+#    #+#                 */
/*   Updated: 2023/08/29 17:24:54 by avon-ben      ########   odam.nl         */
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
	i = 0;
	j = 0;
	if (!map)
		return (0);
	tiles = malloc(sizeof(t_tile **) * (height + 1));
	tiles[height] = NULL;
	if (!tiles)
		return (0);
	while (tiles[i])
	{
		tiles[i] = malloc(sizeof(t_tile *) * (width + 1));
		if (!tiles[i])
			return (0);
		i++;
	}
	tiles[i] = NULL;
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

static void	remove_newline(char **s)
{
	char	*new;

	new = ft_strtrim(*s, "\n");
	free(*s);
	*s = new;
}

void	test(char *addr)
{
	t_map	*map;
	// char	*temp;

	fg_putstr_rgb_fd(addr, "45;255;45", 1);
	write(1, "\n", 1);
	_cub(addr);
	map = mk_map();
	fill_map(map, addr);
	if (!make_tiles(map))
		exit (1);
	// temp = map->color_floor;
	// map->color_floor = ft_strtrim(temp, "\n");
	// free(temp);
	remove_newline(&map->path_ea);
	remove_newline(&map->path_we);
	remove_newline(&map->path_so);
	remove_newline(&map->path_no);
	remove_newline(&map->color_floor);
	remove_newline(&map->color_ceiling);
	// temp = map->color_ceiling;
	// map->color_ceiling = ft_strtrim(temp, "\n");
	// free(temp);
	ft_strrep(map->color_ceiling, ",.-", ';');
	ft_strrep(map->color_floor, ",.-", ';');
	map->color_ceiling = color_syntax(map->color_ceiling);
	map->color_floor = color_syntax(map->color_floor);
	fg_set_rgb_fd(map->color_ceiling, 1);
	fg_set_rgb_fd(map->color_floor, 1);
	check_map(map);
	if (!map->map_arr)
		map_exit("errr");
	if (map)
		write_map(map, 1);
	draw_map(map);
	map = del_map(map);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		ft_putnbr_fd(argc, 1);
		ft_putendl_fd(FG_RED"error\nyou forgot map input"FG_DEFAULT, 1);
		return (1);
	}
	test(argv[1]);
	return (0);
}
	// system("leaks -q cub3D");
