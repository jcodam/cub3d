/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:08:01 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/25 18:36:35 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mlx/include/MLX42/MLX42.h"
#include "mlx/include/KHR/khrplatform.h"
#include "map.h"
#include "libft/libft.h"
#include "defines.h"

// -----------------------------------------------------------------------------

void	draw_minimap(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (j < ft_strlen(map->map_arr[i]))
		{
			if (map->tiles[i][j]->is_wall)
				expand_walls(map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void	mk_rel_vals(t_map *map)
{
	double		p_x;
	double		p_y;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	p_x = map->player.x_coor;
	p_y = map->player.y_coor;
	while (map->tiles[i])
	{
		while (j < ft_strlen(map->map_arr[i]))
		{
			map->tiles[i][j]->rel_x = map->tiles[i][j]->x_coor - p_x;
			map->tiles[i][j]->rel_y = map->tiles[i][j]->y_coor - p_y;
			j++;
		}
		j = 0;
		i++;
	}
}

void	init_direction(t_map *map)
{
	if (map->player.start_direction == P_SOUTH)
		map->player.rot = (PI * 1.5);
	else if (map->player.start_direction == P_WEST)
		map->player.rot = PI;
	else if (map->player.start_direction == P_EAST)
		map->player.rot = 0;
	else
		map->player.rot = (0.5 * PI);
	map->player.x_angle = cos(map->player.rot);
	map->player.y_angle = -sin(map->player.rot);
}

void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_rays		*rays;
	mlx_image_t	*image;

	rays = malloc(sizeof(t_rays));
	map->rays = rays;
	init_rays(rays);
	map->mlx = mlx;
	map->img = img;
	image = mlx_new_image(map->mlx, MAX_X_MINIMAP - MIN_X_MINIMAP, \
		MAX_Y_MINIMAP - MIN_Y_MINIMAP);
	map->mini = image;
	if (!map->mini)
	{
		puts(mlx_strerror(mlx_errno));
		map_exit("Error\nmalloc Error\n");
	}
	draw_box(map);
	convert_coordinates(map);
}

int32_t	draw_map(t_map *map)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	map->img = image;
	if (!map->img)
		return (close_mlx(mlx));
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	make_minimap(map, mlx, image);
	mlx_loop_hook(mlx, ft_move_player, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
