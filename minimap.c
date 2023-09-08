/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:08:01 by avon-ben          #+#    #+#             */
/*   Updated: 2023/09/08 20:41:15 by avon-ben         ###   ########.fr       */
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
#include <math.h>

// -----------------------------------------------------------------------------

float	degToRad(float a)
{
	return (a * PI / 180.0);
}

static void	draw_minimap(t_map *map)
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
	float		p_x;
	float		p_y;
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
		map->player.rotation = 270;
	else if (map->player.start_direction == P_WEST)
		map->player.rotation = 180;
	else if (map->player.start_direction == P_EAST)
		map->player.rotation = 0;
	else
		map->player.rotation = 90;
	map->player.x_angle = cos(degToRad(map->player.rotation));
	map->player.y_angle = -sin(degToRad(map->player.rotation));
}

void	init_rays(t_rays *rays)
{
	rays->mx = 0;
	rays->my = 0;
	rays->ray_x = 0;
	rays->ray_y = 0;
	rays->vert_x = 0;
	rays->vert_y = 0;
	rays->ray_angle = 0;
	rays->offset_x = 0;
	rays->offset_y = 0;
	rays->dist_v = 0;
	rays->dist_h = 0;
	rays->dof = 0;
}

void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_rays		*rays;

	rays = malloc(sizeof(t_rays));
	map->rays = rays;
	init_rays(rays);
	map->mlx = mlx;
	map->img = img;
	draw_box(map);
	convert_coordinates(map);
}

void	draw_direction(t_map *map)
{
	int			i;
	double		x;
	double		y;

	x = get_mmap_centre_x();
	y = get_mmap_centre_y();
	i = 0;
	while (i < 20)
	{
		x += map->player.x_angle;
		y += map->player.y_angle;
		put_pixel_wrap(map->img, (uint32_t)x, (uint32_t)y, \
		ft_pixel(0, 255, 0, 100));
		i++;
	}
}

void	ft_draw_player(void *param)
{
	t_map	*map;
	float	x;
	float	y;
	float	start_x;
	float	start_y;

	map = param;
	draw_background(map);
	start_x = (get_mmap_centre_x() - PLAYER_RAD);
	start_y = (get_mmap_centre_y() - PLAYER_RAD);
	x = start_x;
	y = start_y;
	draw_box(map);
	draw_minimap(map);
	while (x <= (start_x + (PLAYER_RAD * 2)))
	{
		while (y <= (start_y + (PLAYER_RAD * 2)))
			minimap_wrap_print(x, ++y, map, ft_pixel(0, 255, 0, 255));
		y = start_y;
		++x;
	}
	cast_rays(map);
	//draw_direction(map);
}

float FixAng(float a)
{
	if (a > 360)
		a -= 360.0;
	if (a < 0)
		a += 360.0;
	return (a);
}

int check_bckwd(t_map *map, size_t i, size_t j)
{
	float	xc;
	float	xa;
	float	yc;
	float	ya;

	xc = map->player.x_coor;
	xa = map->player.x_angle;
	yc = map->player.y_coor;
	ya = map->player.y_angle;
	if ((map->tiles[i][j]->x_coor - 5) < (xc - (xa * MOVSPEED))
	&& (map->tiles[i][j]->x_coor + (TILE_RAD * 2) + 5) > \
	(xc - (xa * MOVSPEED)) && (map->tiles[i][j]->y_coor - 5) < \
	(yc - (ya * MOVSPEED) + 5) && (map->tiles[i][j]->y_coor + \
	(TILE_RAD * 2) + 5) > (yc - (ya * MOVSPEED)))
		return (1);
	else
		return (0);
}

int check_fwd(t_map *map, size_t i, size_t j)
{
	float	xc;
	float	xa;
	float	yc;
	float	ya;

	xc = map->player.x_coor;
	xa = map->player.x_angle;
	yc = map->player.y_coor;
	ya = map->player.y_angle;
	if ((map->tiles[i][j]->x_coor - 5) < (xc + (xa * MOVSPEED))
	&& (map->tiles[i][j]->x_coor + (TILE_RAD * 2) + 5) > (xc + (xa * MOVSPEED)) \
	&& (map->tiles[i][j]->y_coor - 5) < (yc + (ya * MOVSPEED) + 5) \
	&& (map->tiles[i][j]->y_coor + (TILE_RAD * 2) + 5) > (yc + (ya * MOVSPEED)))
		return (1);
	else
		return (0);
}

int	is_wall(t_map *map, char dir)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (j < ft_strlen(map->map_arr[i]))
		{
			if (dir == 'f' && map->tiles[i][j]->is_wall && check_fwd(map, i, j))
				return (1);
			else if (dir == 'b' && map->tiles[i][j]->is_wall && \
			check_bckwd(map, i, j))
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void move_up(t_map *map)
{
	float	store;

	if (!is_wall(map, 'f'))
	{
		map->player.x_coor += (map->player.x_angle * MOVSPEED);
		map->player.y_coor += (map->player.y_angle * MOVSPEED);
	}
	else if (is_wall(map, 'f'))
	{
		store = map->player.x_angle;
		map->player.x_angle = 0;
		if (!is_wall(map, 'f'))
		{
			map->player.y_coor += map->player.y_angle * MOVSPEED;
		}
		map->player.x_angle = store;
		store = map->player.y_angle;
		map->player.y_angle = 0;
		if (!is_wall(map, 'f'))
			map->player.x_coor += map->player.x_angle * MOVSPEED;
		map->player.y_angle = store;
	}
	mk_rel_vals(map);
}

void move_down(t_map *map)
{
	float	store;

	if (!is_wall(map, 'b'))
	{
		map->player.x_coor -= (map->player.x_angle * MOVSPEED);
		map->player.y_coor -= (map->player.y_angle * MOVSPEED);
	}
	else if (is_wall(map, 'b'))
	{
		store = map->player.x_angle;
		map->player.x_angle = 0;
		if (!is_wall(map, 'b'))
		{
			map->player.y_coor -= map->player.y_angle * MOVSPEED;
		}
		map->player.x_angle = store;
		store = map->player.y_angle;
		map->player.y_angle = 0;
		if (!is_wall(map, 'b'))
			map->player.x_coor -= map->player.x_angle * MOVSPEED;
		map->player.y_angle = store;
	}
	mk_rel_vals(map);
}

void	ft_move_player(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
		move_up(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		move_down(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->player.rotation = FixAng(map->player.rotation + ROTSPEED);
		map->player.x_angle = cos(degToRad(map->player.rotation));
		map->player.y_angle = -sin(degToRad(map->player.rotation));
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player.rotation = FixAng(map->player.rotation - ROTSPEED);
		map->player.x_angle = cos(degToRad(map->player.rotation));
		map->player.y_angle = -sin(degToRad(map->player.rotation));
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	ft_draw_player(map);
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
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
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
	printf("end\n\n");
	return (EXIT_SUCCESS);
}
