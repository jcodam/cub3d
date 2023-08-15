/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 16:27:50 by jbax          #+#    #+#                 */
/*   Updated: 2023/08/15 15:29:29 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft/libft.h"
#include <fcntl.h>
// #include "nextline/get_next_line.h"
char	*get_next_line(int fd);

static char	**get_map(char **temp, int fd)
{
	char	**arr;

	arr = 0;
	while (*temp && **temp && !ft_strempty(*temp))
	{
		arr = ft_arradd_index(arr, *temp, ft_arrlen_c(arr));
		if (!arr)
			map_exit("error\nmalloc error\n");
		*temp = get_next_line(fd);
	}
	return (arr);
}

static void	get_elements(t_map *map, char *temp)
{
	if (!map->path_no && !ft_strncmp(temp, "NO ", 3))
		map->path_no = ft_substr(temp, 2 + ft_skip_whitespace(temp + 2),
				ft_strlen(temp + 2 + ft_skip_whitespace(temp + 2)));
	if (!map->path_so && !ft_strncmp(temp, "SO ", 3))
		map->path_so = ft_substr(temp, 2 + ft_skip_whitespace(temp + 2),
				ft_strlen(temp + 2 + ft_skip_whitespace(temp + 2)));
	if (!map->path_we && !ft_strncmp(temp, "WE ", 3))
		map->path_we = ft_substr(temp, 2 + ft_skip_whitespace(temp + 2),
				ft_strlen(temp + 2 + ft_skip_whitespace(temp + 2)));
	if (!map->path_ea && !ft_strncmp(temp, "EA ", 3))
		map->path_ea = ft_substr(temp, 2 + ft_skip_whitespace(temp + 2),
				ft_strlen(temp + 2 + ft_skip_whitespace(temp + 2)));
	if (!map->color_floor && !ft_strncmp(temp, "F ", 2))
		map->color_floor = ft_substr(temp, 1 + ft_skip_whitespace(temp + 1),
				ft_strlen(temp + 1 + ft_skip_whitespace(temp + 1)));
	if (!map->color_ceiling && !ft_strncmp(temp, "C ", 2))
		map->color_ceiling = ft_substr(temp, 1 + ft_skip_whitespace(temp + 1),
				ft_strlen(temp + 1 + ft_skip_whitespace(temp + 1)));
}

int	fill_map(t_map *map, char const *path)
{
	int		fd;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd < 2)
		map_exit("error\ncan't open the .cub, check address\n");
	temp = get_next_line(fd);
	while (temp)
	{
		get_elements(map, temp);
		if (check_map_full(map) == 2 && ft_strinset(temp, "10NWES \n")
			&& !ft_strempty(temp))
			map->map_arr = get_map(&temp, fd);
		if (temp)
			free(temp);
		temp = get_next_line(fd);
	}
	if (check_map_full(map))
		map_exit("error\ncouldn't fill map. necessary data are missing\n");
	close(fd);
	return (1);
}

t_map	*mk_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (0);
	map->color_ceiling = 0;
	map->color_floor = 0;
	map->map_arr = 0;
	map->path_ea = 0;
	map->path_no = 0;
	map->path_so = 0;
	map->path_we = 0;
	map->player.start_direction = EMPTY;
	map->player.map_x = 0;
	map->player.map_y = 0;
	map->tiles = NULL;
	//map->minimap = malloc(sizeof(t_minimap *));
	return (map);
}

int	write_map(t_map *map, int fd)
{
	if (!map)
		return (0);
	if (map->color_ceiling)
		ft_putendl_fd(map->color_ceiling, fd);
	if (map->color_floor)
		ft_putendl_fd(map->color_floor, fd);
	if (map->path_ea)
		ft_putendl_fd(map->path_ea, fd);
	if (map->path_no)
		ft_putendl_fd(map->path_no, fd);
	if (map->path_so)
		ft_putendl_fd(map->path_so, fd);
	if (map->path_we)
		ft_putendl_fd(map->path_we, fd);
	if (map->map_arr)
	{
		ft_putarrs_fd(map->map_arr, fd);
		ft_putnbr_fd(ft_arrlen_c(map->map_arr), 1);
		write(1, "\n", 1);
	}
	return (0);
}
