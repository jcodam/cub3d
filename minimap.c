/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:08:01 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/08/02 18:13:23 by avon-ben      ########   odam.nl         */
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

//static	mlx_image_t* image;

// -----------------------------------------------------------------------------

static void	put_pixel_wrap(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		mlx_put_pixel(image, x, y, color);
	}
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	minimap_wrap_print(double x, double y, t_map *map, int32_t colour)
{
	if ((int)x < MAX_X_MINIMAP && (int)x > MIN_X_MINIMAP && \
	(int)y < MAX_Y_MINIMAP && (int)y > MIN_Y_MINIMAP)
		put_pixel_wrap(map->minimap->img, (int)x, (int)y, colour);
}

double	c_to_mini(t_map *map, int i, int j, char x_or_y)
{
	if (x_or_y == 'x')
		return (map->tiles[i][j]->rel_x + MIN_X_MINIMAP + ((MAX_X_MINIMAP - MIN_X_MINIMAP) / 2));
	else
		return (map->tiles[i][j]->rel_y + MIN_Y_MINIMAP + ((MAX_Y_MINIMAP - MIN_Y_MINIMAP) / 2));
}

size_t	mini_x(size_t x)
{
	return (x + MIN_X_MINIMAP + ((MAX_X_MINIMAP - MIN_X_MINIMAP) / 2));
}

size_t	mini_y(size_t y)
{
	return (y + MIN_Y_MINIMAP + ((MAX_Y_MINIMAP - MIN_Y_MINIMAP) / 2));
}

void	expand_walls(t_map *map, int i, int j)
{
	size_t	x;
	double	y;
	double	start_x;
	double	start_y;

	x = c_to_mini(map, i, j, 'x') - TILE_RAD;
	y = c_to_mini(map, i, j, 'y') - TILE_RAD;
	start_x = x;
	start_y = y;
	while (x < (start_x + (TILE_RAD * 2)))
	{
		while (y < (start_y + (TILE_RAD * 2)))
		{
			minimap_wrap_print(x, y, map, ft_pixel(255, 0, 0, 255));
			y++;
		}
		y = start_y;
		x++;
	}
}

static void	draw_minimap(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			if (!map->tiles[i][j]->is_open && !map->tiles[i][j]->not_map)
				expand_walls(map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void mk_rel_vals(t_map *map)
{
	size_t	p_x;
	size_t	p_y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	p_x = map->player.x_coor;
	p_y = map->player.y_coor;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			map->tiles[i][j]->rel_x = p_x - map->tiles[i][j]->x_coor;
			map->tiles[i][j]->rel_y = p_y - map->tiles[i][j]->y_coor;
			j++;
		}
		j = 0;
		i++;
	}
}

static void	init_direction(t_player player)
{
	if (player.start_direction == 10)
		player.rotation = 0;
	if (player.start_direction == 11)
		player.rotation = 90;
	if (player.start_direction == 12)
		player.rotation = 180;
	if (player.start_direction == 13)
		player.rotation = 270;
}

static void	init_player(t_map *map)
{
	map->player.x_coor = map->player.start_x;
	map->player.y_coor = map->player.start_y;
	init_direction(map->player);
}

void	convert_coordinates(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			map->tiles[i][j]->x_coor = ((TILE_RAD / 2) + (i * TILE_RAD));
			map->tiles[i][j]->y_coor = ((TILE_RAD / 2) + (j * TILE_RAD));
			if (map->tiles[i][j]->is_player)
			{
				init_player(map);
				map->player.start_x = map->tiles[i][j]->x_coor;
				map->player.start_x = map->tiles[i][j]->y_coor;
			}
			j++;
		}
		j = 0;
		i++;
	}
	mk_rel_vals(map);
}

void	shade_box(t_map *map)
{
	int	x;
	int	y;

	x = MIN_X_MINIMAP;
	y = MIN_Y_MINIMAP;
	while (x < MAX_X_MINIMAP)
	{
		while (y < MAX_Y_MINIMAP)
		{
			put_pixel_wrap(map->minimap->img, x, y, \
			ft_pixel(255, 255, 255, 255));
			y++;
		}
		y = MIN_Y_MINIMAP;
		x++;
	}
}

static void	draw_box(t_map *map)
{
	int	x;
	int	y;

	shade_box(map);
	x = (MIN_X_MINIMAP);
	y = (MIN_Y_MINIMAP);
	while (y < MAX_Y_MINIMAP)
	{
		put_pixel_wrap(map->minimap->img, x, y, 0xFFFFFFFF);
		put_pixel_wrap(map->minimap->img, (x + (MAX_X_MINIMAP - \
		MIN_X_MINIMAP)), y, 200);
		y++;
	}
	y = (MIN_Y_MINIMAP);
	while (x < MAX_X_MINIMAP)
	{
		put_pixel_wrap(map->minimap->img, x, y, 0xFFFFFFFF);
		put_pixel_wrap(map->minimap->img, x, (y + (MAX_Y_MINIMAP - \
		MIN_Y_MINIMAP)), 200);
		x++;
	}
}

void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	int			i;
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	i = 0;
	minimap->mlx = mlx;
	minimap->img = img;
	map->minimap = minimap;
	draw_box(map);
	convert_coordinates(map);
	draw_minimap(map);
	init_direction(map->player);
}

void ft_draw_player(void *param)
{
	t_map	*map;
	size_t	x;
	size_t	y;
	size_t	start_x;
	size_t	start_y;

	map = param;
	x = mini_x(map->player.x_coor);
	y = mini_y(map->player.y_coor);
	start_x = x - PLAYER_RAD;
	start_y = y - PLAYER_RAD;
	draw_box(map);
	draw_minimap(map);
	while (x <= (start_x + (PLAYER_RAD * 2)))
	{
		while (y <= (start_y + (PLAYER_RAD * 2)))
		{
			minimap_wrap_print((double)x, (double)y, map, \
			ft_pixel(255, 0, 0, 255));
			y++;
		}
		y = start_y;
		x++;
	}
}

int in_range_xy(t_map *map, int i, int j, double check_val, char x_y)
{
	double	ref;

	if (x_y == 'x')
	{
		ref = map->tiles[i][j]->x_coor;
		if (ref > (check_val - TILE_RAD) && ref < (check_val + TILE_RAD))
			return (1);
	}
	else if (x_y == 'y')
	{
		ref = map->tiles[i][j]->y_coor;
		if (ref > (check_val - TILE_RAD) && ref < (check_val + TILE_RAD))
			return (1);
	}
	return (0);
}

static int in_wall(int p_x, int p_y, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			printf("map tile [%d][%d], x_coor: %f, y_coor: %f\n", i, j, map->tiles[i][j]->x_coor, map->tiles[i][j]->y_coor);
			if (in_range_xy(map, i, j, (double)p_x, 'x' && !map->tiles[i][j]->is_open) \
			&& in_range_xy(map, i, j, (double)p_y, 'y') && !map->tiles[i][j]->is_open)
			{
				printf("player x: %f, player y: %f\ntile x: %f, tile y: %f\n\n", (double)p_x, (double)p_y, map->tiles[i][j]->x_coor, map->tiles[i][j]->y_coor);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	ft_move_player(void *param)
{
	t_map	*map;
	int		x;
	int		y;

	map = param;
	x = map->player.x_coor;
	y = map->player.y_coor;
	printf("player x: %d, player y: %d\n", x, y);
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_UP) && !in_wall(x, (y -1), map))
	{
		//map->player.map_y--;
		map->player.y_coor--;
	}
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_DOWN) && !in_wall(x, y + 1, map))
	{
		//map->player.map_y++;
		map->player.y_coor++;
	}
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_LEFT) && !in_wall((x -1), y, map))
	{
		map->player.x_coor--;
		// if (map->player.rotation == 0)
		// 	map->player.rotation = 359;
		// else
		// 	map->player.rotation--;
	}
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_RIGHT) && !in_wall(x + 1, y, map))
	{
		map->player.x_coor++;
		// if (map->player.rotation == 359)
		// 	map->player.rotation = 0;
		// else
		// 	map->player.rotation++;
	}
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

	i = MIN_X_MINIMAP;
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!map->minimap->img)
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
