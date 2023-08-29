/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:08:01 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/08/29 19:40:12 by avon-ben      ########   odam.nl         */
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
#include "math.h"

// -----------------------------------------------------------------------------

float	degToRad(int a)
{
	return (a * M_PI / 180.0);
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
	if (map->player.start_direction == 11)
		map->player.rotation = 270;
	else if (map->player.start_direction == 12)
		map->player.rotation = 180;
	else if (map->player.start_direction == 13)
		map->player.rotation = 0;
	else
		map->player.rotation = 90;
	map->player.x_angle = cos(degToRad(map->player.rotation));
	map->player.y_angle = -sin(degToRad(map->player.rotation));
}

void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	t_rays		*rays;

	rays = malloc(sizeof(t_rays));
	map->rays = rays;
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
	//while (pix_not_wall(map, x + map->player.x_angle, y + map->player.y_angle))
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
	//draw_direction(map);
	draw_rays(map);
}

int FixAng(int a)
{
	if (a > 360)
		a -= 360;
	if (a <= 0)
		a += 360;
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
	if ((map->tiles[i][j]->x_coor - 5) < (xc - (xa * 2))
	&& (map->tiles[i][j]->x_coor + (TILE_RAD * 2) + 5) > (xc - (xa * 2)) \
	&& (map->tiles[i][j]->y_coor - 5) < (yc - (ya * 2) + 5) \
	&& (map->tiles[i][j]->y_coor + (TILE_RAD * 2) + 5) > (yc - (ya * 2)))
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
	if ((map->tiles[i][j]->x_coor - 5) < (xc + (xa * 2))
	&& (map->tiles[i][j]->x_coor + (TILE_RAD * 2) + 5) > (xc + (xa * 2)) \
	&& (map->tiles[i][j]->y_coor - 5) < (yc + (ya * 2) + 5) \
	&& (map->tiles[i][j]->y_coor + (TILE_RAD * 2) + 5) > (yc + (ya * 2)))
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
		map->player.x_coor += (map->player.x_angle * 2);
		map->player.y_coor += (map->player.y_angle * 2);
	}
	else if (is_wall(map, 'f'))
	{
		store = map->player.x_angle;
		map->player.x_angle = 0;
		if (!is_wall(map, 'f'))
		{
			map->player.y_coor += map->player.y_angle * 2;
		}
		map->player.x_angle = store;
		store = map->player.y_angle;
		map->player.y_angle = 0;
		if (!is_wall(map, 'f'))
			map->player.x_coor += map->player.x_angle * 2;
		map->player.y_angle = store;
	}

	mk_rel_vals(map);
}

void move_down(t_map *map)
{
	float	store;

	if (is_wall(map, 'b'))
	{
		store = map->player.x_angle;
		map->player.x_angle = 0;
		if (!is_wall(map, 'b'))
			map->player.y_coor -= map->player.y_angle * 2;
		else
			map->player.x_coor -= store * 2;
		map->player.x_angle = store;
	}
	else
	{
		map->player.x_coor -= (map->player.x_angle * 2);
		map->player.y_coor -= (map->player.y_angle * 2);
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
		map->player.rotation = FixAng(map->player.rotation + 2);
		map->player.x_angle = cos(degToRad(map->player.rotation));
		map->player.y_angle = -sin(degToRad(map->player.rotation));
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->player.rotation = FixAng(map->player.rotation - 2);
		map->player.x_angle = cos(degToRad(map->player.rotation));
		map->player.y_angle = -sin(degToRad(map->player.rotation));
	}
	ft_draw_player(map);
}

static void player_movement(mlx_t *mlx, t_map *map)
{
	mlx_loop_hook(mlx, ft_move_player, map);
	mlx_loop_hook(mlx, ft_draw_player, map);
}

int32_t	draw_map(t_map *map)
{
	mlx_t		*mlx;
	int			i;
	mlx_image_t	*image;
	int			a;

	a = 1;
	i = MIN_X_MINIMAP;
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
	player_movement(mlx, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
