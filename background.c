/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:51:40 by jbax              #+#    #+#             */
/*   Updated: 2023/09/08 21:27:38 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
// #include <float.h>
#include "map.h"
#include "libft/libft.h"
#include "defines.h"

// static void	texture_scale(mlx_image_t *img, mlx_texture_t *png,
// 	double width, double height)
// {
// 	unsigned int	count;
// 	double			count2;
// 	double			count3;
// 	unsigned int	iii;
// 	double			www;
// 	// double	hhh;
// 	// int

// 	(void)width;
// 	(void)height;
// 	count = 0;
// 	www = ((width / png->width) * 1000);
// 	www = ((int)www % 1000);
// 	www = www / 1000;
// 	count2 = (double)png->width / width;
// 	count3 = (double)png->height / height;
// 	iii = 0;
// 	while (iii < height)
// 	{
// 		while (count < width)
// 		{
// 			ft_memcpy(img->pixels + (int)(WIDTH * (int)((HEIGHT / 2 - height / 2) + iii) + count) * 4,
// 				png->pixels +
// 				(int)(png->width * (int)(iii * count3) + count * count2) * 4,
// 				png->bytes_per_pixel);
// 			count++;
// 		}
// 		count = 0;
// 		iii++;
// 	}
// }

static void	texture_s(mlx_image_t *img, mlx_texture_t *png,
	double angle, int point_png, double height)
{
	unsigned int	count;
	unsigned int	iii;
	double			count3;
	double			width;

	width = png->width;
	if (RAY_X_PIXEL_WIDTH)
		width = RAY_X_PIXEL_WIDTH;
	count = point_png;
	count3 = (double)png->height / height;
	iii = 0;
	while (iii < height && iii < height - ((height - HEIGHT) / 2))
	{
		while ((height - HEIGHT) / 2 > iii)
			iii++;
		while (count - point_png < width && angle + (count - point_png) < WIDTH)
		{
			ft_memcpy(
				img->pixels + (int)(WIDTH * (int)(((HEIGHT - height) / 2) + iii)
					+ (angle) + count - point_png) * 4, png->pixels + \
				(int)(png->width * (int)(iii * count3) + count) * 4,
				png->bytes_per_pixel);
			count++;
		}
		count = point_png;
		iii++;
	}
}
//  + angle * (WIDTH / (FOV * 2)) -- * ( (FOV * FOVTIMES) / WIDTH )
/*2--16.924805--592.924805--1599.999878--119*/

static double	modulo_dbl(double res, double mod)
{
	while (res >= mod)
		res = res - mod;
	return (res);
}
/*if (angle == 2)
	{
	printf("%d--%f--%f--%f--%d\n", angle, modulo_dbl(map->rays->ray_y , 64)
	, map->rays->ray_y, map->rays->ray_x, (int)map->rays->ray_angle );
	// exit(0);
	}*/

void	wall_texture(t_map *map, double distence, int angle, double point_png)
{
	double			height;
	int				i;

	height = (map->height * HEIGHT / distence) * 2;
	if (point_png > 0)
	{
		i = 0;
		i = modulo_dbl(map->rays->ray_y, 64);
		if (map->rays->ray_angle < 90 || (int)map->rays->ray_angle > 270)
			texture_s(map->img, map->png->png_ea, angle - 1, i, height);
		else
			texture_s(map->img, map->png->png_we, angle - 1, i, height);
	}
	else
	{
		i = modulo_dbl(map->rays->ray_x, 64);
		if (map->rays->ray_angle < 180)
			texture_s(map->img, map->png->png_no, angle - 1, i, height);
		else
			texture_s(map->img, map->png->png_so, angle - 1, i, height);
	}
}

void	draw_background(t_map *map)
{
	int				pos_width;
	int				pos_height;
	int				floor;
	int				ceiling;

	ceiling = map->png->color_ceiling;
	floor = map->png->color_floor;
	pos_width = 0;
	pos_height = 0;
	while (pos_height != HEIGHT)
	{
		while (pos_width != WIDTH)
		{
			if (pos_height < HEIGHT / 2)
				mlx_put_pixel(map->img, pos_width, pos_height, ceiling);
			else
				mlx_put_pixel(map->img, pos_width, pos_height, floor);
			pos_width++;
		}
		pos_width = 0;
		pos_height++;
	}
	// texture_scale(map->img, map->png->png_no, 640, 640);
}
