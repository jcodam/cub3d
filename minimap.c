/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:08:01 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/07/28 18:11:02 by avon-ben      ########   odam.nl         */
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

static	mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	minimap_wrap_print(double x, double y)
{
	if ((int)x < MAX_X_MINIMAP && (int)x > MIN_X_MINIMAP && \
	(int)y < MAX_Y_MINIMAP && (int)y > MIN_Y_MINIMAP)
		mlx_put_pixel(image, (int)x, (int)y, ft_pixel(255, 255, 255, 255));
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
			minimap_wrap_print(x, y);
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
	double	w_int;
	double	h_int;

	i = 0;
	j = 0;
	w_int = (MAX_X_MINIMAP - MIN_X_MINIMAP) / map->width;
	h_int = (MAX_Y_MINIMAP - MIN_Y_MINIMAP) / map->height;
	printf("w_int: %f\n", w_int);
	printf("h_int: %f\n", h_int);
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			map->tiles[i][j]->x_coor = MIN_X_MINIMAP + \
			((map->tiles[i][j]->x + 1) * w_int);
			map->tiles[i][j]->y_coor = MIN_Y_MINIMAP + \
			((map->tiles[i][j]->y + 1) * h_int);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

void	shade_box(void)
{
	int	x;
	int	y;

	x = MIN_X_MINIMAP;
	y = MIN_Y_MINIMAP;
	while (x < MAX_X_MINIMAP)
	{
		while (y < MAX_Y_MINIMAP)
		{
			mlx_put_pixel(image, x, y, ft_pixel(255, 255, 255, 10));
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

	(void)map;
	shade_box();
	x = (MIN_X_MINIMAP);
	y = (MIN_Y_MINIMAP);
	while (y < MAX_Y_MINIMAP)
	{
		mlx_put_pixel(image, x, y, 0xFFFFFFFF);
		mlx_put_pixel(image, (x + (MAX_X_MINIMAP - MIN_X_MINIMAP)), y, 200);
		y++;
	}
	y = (MIN_Y_MINIMAP);
	while (x < MAX_X_MINIMAP)
	{
		mlx_put_pixel(image, x, y, 0xFFFFFFFF);
		mlx_put_pixel(image, x, ((y - 1) + (MAX_Y_MINIMAP - MIN_Y_MINIMAP)), \
		200);
		x++;
	}
}	

void	make_minimap(t_map *map, mlx_t *mlx)
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
	minimap->img = NULL;
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
}

// -----------------------------------------------------------------------------

int	check_mlx_error(mlx_t *mlx)
{
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (0);
	}
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (0);
	}
	return (1);
}

void ft_draw_player(void *param)
{
	t_map	*map;
	int		x;
	int		y;
	int		start_x;
	int		start_y;

	map = param;
	x = map->player.map_x;
	y = map->player.map_y;
	start_x = x;
	start_y = y;
	x -= 2;
	y -= 2;
	while (x < (start_x + 4))
	{
		while (y < (start_y + 4))
		{
			mlx_put_pixel(image, x, y, 0xFF00FFFF);
			y++;
		}
		y = start_y;
		x++;
	}
}

void	ft_move_player(void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_UP))
		map->player.map_y -= 1;
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_DOWN))
		map->player.map_y += 1;
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_LEFT))
		map->player.map_x -= 1;
	if (mlx_is_key_down(map->minimap->mlx, MLX_KEY_RIGHT))
		map->player.map_x += 1;
}

int32_t	draw_map(t_map *map)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!check_mlx_error(mlx))
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	make_minimap(map, mlx);
	mlx_loop_hook(mlx, ft_draw_player, map);
	mlx_loop_hook(mlx, ft_move_player, map);
	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
