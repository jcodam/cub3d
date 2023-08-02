/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_errors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 17:40:36 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/28 16:43:35 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "color.h"
#include "map.h"

void	map_exit(char *str)
{
	fg_putstr_rgb_fd(str,"200;0;0", 1);
	exit(0);
}

// void	find_error(t_map *cep, int i, int x)
// {
// 	if (cep->map_c < 1)
// 		map_exit("Error\nno sluge to collect in map\n");
// 	if (cep->map_e < 1)
// 		map_exit("Error\nno exit in map\n");
// 	if (cep->map_e > 1)
// 		map_exit("Error\nmore than 1 exit in map\n");
// 	if (cep->map_p < 1)
// 		map_exit("Error\nno player in map\n");
// 	if (cep->map_p > 1)
// 		map_exit("Error\nmore than 1 player in map\n");
// 	if (i != x)
// 		map_exit("Error\nmap is not rectangular\n");
// }

// int	map(t_map *map)
// {
// 	if (!map)
// 		return (0);
// 	if (map->color_ceiling)
// 		free(map->color_ceiling);
// 	if (map->color_floor)
// 		free(map->color_floor);
// 	if (map->map_arr)
// 	{
// 		ft_arrclear_c(map->map_arr, ft_arrlen_c(map->map_arr));
// 	}
// 	if (map->path_ea)
// 		free(map->path_ea);
// 	if (map->path_no)
// 		free(map->path_no);
// 	if (map->path_so)
// 		free(map->path_so);
// 	if (map->path_we)
// 		free(map->path_we);
// 	free(map);
// 	return (0);
// }

void	_cub(char *arg)
{
	int		i;
	char	*str;

	i = 0;
	str = ".cub";
	while (arg[i] != '.' && arg[i])
		i++;
	while (arg[i] == *str && arg[i] && *str)
	{
		str++;
		i++;
	}
	if (arg[i] || *str)
		map_exit("Error\nno .cub file given as input\n");
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
		ft_arrclear_c(map->map_arr, ft_arrlen_c(map->map_arr));
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
