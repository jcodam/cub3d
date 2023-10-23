/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:11:24 by avon-ben          #+#    #+#             */
/*   Updated: 2023/10/23 18:18:13 by avon-ben         ###   ########.fr       */
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

void	ft_draw_player(void *param)
{
	t_map	*map;
	double	x;
	double	y;
	double	start_x;
	double	start_y;

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
	if (map->is_mini > 0)
		image_to_image(map->img, map->mini, 0, 0);
}

double	fixang(double a)
{
	if (a > (2 * PI))
		a -= (2 * PI);
	if (a < 0)
		a += (2 * PI);
	return (a);
}

void	init_rays(t_rays *rays)
{
	rays->ray_x = 0;
	rays->ray_y = 0;
	rays->vert_x = 0;
	rays->vert_y = 0;
	rays->ray_angle = 0;
	rays->offset_x = 0;
	rays->offset_y = 0;
	rays->dist_v = 0;
	rays->dist_h = 0;
}

int	close_mlx(mlx_t *mlx)
{
	mlx_close_window(mlx);
	puts(mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}
