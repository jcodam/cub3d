/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 16:27:50 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/13 17:34:17 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft/libft.h"
#include <fcntl.h>
// #include "nextline/get_next_line.h"
char	*get_next_line(int fd);

int	fill_map(t_map *map, char const *path)
{
	int		fd;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd < 2)
		return (0);
	temp = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		if (!ft_strncmp(temp, "NO", 2))
			map->path_no = ft_substr(temp, 3, ft_strlen(temp) - 2);
		free(temp);
		temp = get_next_line(fd);
	}
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
	return (map);
}

t_map	*del_map(t_map *map)
{
	if (!map)
		return (0);
	if (map->color_ceiling)
		free(map->color_ceiling);
	if (map->color_floor)
		free(map->color_floor);
	if (map->map_arr)
	{
		while (*map->map_arr)
		{
			free(*map->map_arr);
			map->map_arr++;
		}
		free(map->map_arr);
	}
	if (map->path_ea)
		free(map->path_ea);
	if (map->path_no)
		free(map->path_no);
	if (map->path_so)
		free(map->path_so);
	if (map->path_we)
		free(map->path_we);
	free(map);
	return (0);
}
