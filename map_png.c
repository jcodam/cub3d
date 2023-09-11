/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_png.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:05:36 by jbax              #+#    #+#             */
/*   Updated: 2023/09/11 16:30:19 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft/libft.h"
#include "defines.h"

static int	get_collors(char *collor)
{
	char	**temp;
	int		value;
	int		count;

	count = 0;
	temp = ft_split(collor, ';');
	if (!temp)
		map_exit("Error\nmalloc Error\n");
	value = ft_pixel(ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2]), 200);
	while (temp[count])
	{
		free(temp[count]);
		count++;
	}
	free(temp);
	return (value);
}

void	mk_png(t_map *map)
{
	map->is_mini = -1;
	map->png = malloc(sizeof(t_png));
	if (!map->png)
		map_exit("Error\nmalloc Error\n");
	map->png->png_ea = mlx_load_png(map->path_ea);
	if (!map->png->png_ea)
		map_exit("Error\npng east didn't load\n");
	map->png->png_no = mlx_load_png(map->path_no);
	if (!map->png->png_no)
		map_exit("Error\npng north didn't load\n");
	map->png->png_so = mlx_load_png(map->path_so);
	if (!map->png->png_so)
		map_exit("Error\npng south didn't load\n");
	map->png->png_we = mlx_load_png(map->path_we);
	if (!map->png->png_we)
		map_exit("Error\npng west didn't load\n");
	map->png->color_ceiling = get_collors(map->color_ceiling);
	map->png->color_floor = get_collors(map->color_floor);
}

int	check_png_full(t_map *map)
{
	if (!map->png)
		return (1);
	if (!map->png->color_ceiling)
		return (CEILING);
	if (!map->png->color_floor)
		return (FLOOR);
	if (!map->png->png_ea)
		return (P_EAST);
	if (!map->png->png_no)
		return (P_NORTH);
	if (!map->png->png_so)
		return (P_SOUTH);
	if (!map->png->png_we)
		return (P_WEST);
	return (0);
}

t_map	*del_png_s(t_map *map)
{
	if (!map)
		return (0);
	if (!map->png)
		return (map);
	if (map->png->png_ea)
		mlx_delete_texture(map->png->png_ea);
	if (map->png->png_no)
		mlx_delete_texture(map->png->png_no);
	if (map->png->png_so)
		mlx_delete_texture(map->png->png_so);
	if (map->png->png_we)
		mlx_delete_texture(map->png->png_we);
	free(map->png);
	map->png = 0;
	return (map);
}
