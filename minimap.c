/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:08:01 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/08/02 14:34:15 by avon-ben      ########   odam.nl         */
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

void	expand_walls(t_map *map, int i, int j)
{
	double	x;
	double	y;
	double	start_x;
	double	start_y;

	x = (map->tiles[i][j]->x_coor - (map->tiles[i][j]->width / 2));
	y = (map->tiles[i][j]->y_coor - (map->tiles[i][j]->height / 2));
	start_x = x;
	start_y = y;
	while (x < (start_x + map->tiles[i][j]->width))
	{
		while (y < (start_y + map->tiles[i][j]->height))
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

void	convert_coordinates(t_map *map)
{
	int		i;
	int		j;
	//double	w_int;
	//double	h_int;
	int		interval;

	i = 0;
	j = 0;
	interval = 10;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			map->tiles[i][j]->x_coor = MIN_X_MINIMAP + \
			((map->tiles[i][j]->x + 1) * interval);
			map->tiles[i][j]->y_coor = MIN_Y_MINIMAP + \
			((map->tiles[i][j]->y + 1) * interval);
			if (map->tiles[i][j]->is_player)
			{
				map->player.x_coor = map->tiles[i][j]->x_coor;
				map->player.y_coor = map->tiles[i][j]->y_coor;	
			}
			j++;
		}
		j = 0;
		i++;
	}
}

// void	ft_hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

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

void	init_direction(t_player player)
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

void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img)
{
	size_t		height;
	size_t		width;
	int			i;
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	i = 0;
	height = 0;
	width = 0;
	minimap->mlx = mlx;
	minimap->img = img;
	map->minimap = minimap;
	while (map->map_arr[i])
	{
		if (ft_strlen(map->map_arr[i]) > width)
			width = ft_strlen(map->map_arr[i]);
		height++;
		i++;
	}
	width--;
	draw_box(map);
	convert_coordinates(map);
	draw_minimap(map);
	init_direction(map->player);
}

// void draw_angle(t_map *map, int x, int y, int rotation)
// {
// 	if (rotation >= 0 && rotation < 90)

// 	if (rotation >= 90 && rotation < 180

// 	if (rotation
// }


void ft_draw_player(void *param)
{
	t_map	*map;
	int		x;
	int		y;
	int		start_x;
	int		start_y;

	map = param;
	x = (map->player.map_x + ((MIN_X_MINIMAP + MAX_X_MINIMAP) / 2));
	y = (map->player.map_y + ((MIN_Y_MINIMAP + MAX_Y_MINIMAP) / 2));
	start_x = x;
	start_y = y;
	x -= 2;
	y -= 2;
	draw_box(map);
	draw_minimap(map);
	while (x < (start_x + 4))
	{
		while (y < (start_y + 4))
		{
			minimap_wrap_print((double)x, (double)y, map, \
			ft_pixel(255, 0, 0, 255));
			y++;
		}
		y = (start_y - 2);
		x++;
	}
	//draw_angle(map, start_x, start_y, map->player.rotation);
}

int in_range_xy(t_map *map, int i, int j, double check_val, char x_y)
{ 
	double ref;
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
		map->player.map_y--;
		map->player.y_coor--;
	}
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_DOWN) && !in_wall(x, y + 1, map))
	{
		map->player.map_y++;
		map->player.y_coor++;
	}
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_LEFT) && !in_wall((x -1), y, map))
	{
		if (map->player.rotation == 0)
			map->player.rotation = 359;
		else
			map->player.rotation--;
	}
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_RIGHT)) //&& !in_wall(x + 1, y, map))
	{
		if (map->player.rotation == 359)
			map->player.rotation = 0;
		else
			map->player.rotation++;
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
