/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:40:36 by jbax              #+#    #+#             */
/*   Updated: 2023/09/07 16:22:58 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "color.h"
#include "map.h"

void	map_exit(char *str)
{
	fg_putstr_rgb_fd(str, "200;0;0", 1);
	exit(0);
}

int	_cub(char *arg)
{
	int		i;
	char	*str;

	i = 0;
	str = ".cub";
	str = ft_strnstr(arg, ".cub", ft_strlen(arg));
	if (!str)
		map_exit("Error\nno .cub file given as input\n");
	if (!str[4])
		return (1);
	if (_cub(str + 4))
		return (1);
	return (0);
}

char	*color_syntax(char *str)
{
	char	**temp;
	char	*dest;

	if (!ft_strinset(str, "0987654321;\n"))
		map_exit("error\na color value must consist only of numbers and ,.-\n");
	temp = ft_split(str, ';');
	if (!temp)
		map_exit("error\nsplitting or malloc of colors failed\n");
	if (ft_arrlen_c(temp) != 3)
		map_exit("error\ncolor value has more or less than 3numbers\n");
	if (ft_atoi(temp[0]) > 255)
		map_exit("error\ncolor value higher than 255 found\n");
	if (ft_atoi(temp[1]) > 255)
		map_exit("error\ncolor value higher than 255 found\n");
	if (ft_atoi(temp[2]) > 255)
		map_exit("error\ncolor value higher than 255 found\n");
	dest = ft_strjoinx(5, temp[0], ";", temp[1], ";", temp[2]);
	ft_arrclear_c(temp, ft_arrlen_c(temp));
	free(str);
	return (dest);
}

int	check_map_full(t_map *map)
{
	if (!map)
		return (1);
	if (!map->color_ceiling)
		return (CEILING);
	if (!map->color_floor)
		return (FLOOR);
	if (!map->path_ea)
		return (P_EAST);
	if (!map->path_no)
		return (P_NORTH);
	if (!map->path_so)
		return (P_SOUTH);
	if (!map->path_we)
		return (P_WEST);
	if (!map->map_arr)
	{
		return (2);
	}
	return (0);
}


static void free_tiles(t_map *map)
{
	int i;
	int j;

	i = 0; 
	j = 0;
	if (map)
	{
		if (map->tiles)
		{
			while (i < map->height)
			{
				if (map->tiles[i])
				{
					while (j < map->width)
					{
						if (map->tiles[i][j])
						{
							free(map->tiles[i][j]);
						}
						j++;
					}
				}
				free(map->tiles[i]);
				j = 0;
				i++;
			}
		free (map->tiles);
		}
	}
}

static void free_map_arr(t_map *map)
{
	int	i;

	i = 0;
	if (!map->map_arr)
		return ;
	if (map->map_arr)
	{
		while (map->map_arr[i])
		{
			if (map->map_arr[i])
				free (map->map_arr[i]);
			i++;
		}
		free(map->map_arr);
	}
}

t_map	*del_map(t_map *map)
{
	printf("map->width: %d\n", map->width);
	if (!map)
		return (0);
	printf("del_map\n\n\n");
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
	free_tiles(map);
	if (map->rays)
		free(map->rays);
	//free(map);
	return (0);
}
