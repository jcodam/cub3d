/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:51:39 by jbax              #+#    #+#             */
/*   Updated: 2023/10/23 17:46:53 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
// #include <float.h>
#include "map.h"
#include "libft/libft.h"
#include "defines.h"

static void	texture_s(mlx_image_t *img, mlx_texture_t *png,
	int point_png, double *height)
{
	unsigned int	iii;
	unsigned int	les_load;
	double			count3;
	int				les_l;

	les_l = ((HEIGHT - height[0]) / 2);
	les_load = height[0] - ((height[0] - HEIGHT) / 2);
	count3 = (double)png->height / height[0];
	iii = 0;
	if (iii < (height[0] - HEIGHT) / 2)
		iii = (height[0] - HEIGHT) / 2;
	while (iii < height[0] && iii < les_load)
	{
		if (height[1] < WIDTH)
		{
			ft_memcpy(
				img->pixels + (int)(WIDTH * (int)(les_l
						+ iii) + height[1])*4, png->pixels + \
				(int)(png->width * (int)(iii * count3) + point_png) * 4,
				png->bytes_per_pixel);
		}
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

void	wall_texture(t_map *map, double distence, int i_value, double point_png)
{
	double			height[2];
	int				i;

	height[0] = (25 * HEIGHT / distence) * 2;
	height[1] = WIDTH - i_value;
	if (point_png > 0)
	{
		i = modulo_dbl(map->rays->ray_y, TD);
		if (map->rays->ray_angle <= (PI * 0.5) \
		|| map->rays->ray_angle >= (PI * 1.5))
			texture_s(map->img, map->png->png_ea, i, height);
		else
			texture_s(map->img, map->png->png_we, i, height);
	}
	else
	{
		i = modulo_dbl(map->rays->ray_x, TD);
		if (map->rays->ray_angle < PI)
			texture_s(map->img, map->png->png_no, i, height);
		else
			texture_s(map->img, map->png->png_so, i, height);
	}
}
