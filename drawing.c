/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:37:50 by avon-ben          #+#    #+#             */
/*   Updated: 2023/09/11 17:04:40 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"

void	put_pixel_wrap(mlx_image_t *image, int x, int y, uint32_t color)
{
	x -= MIN_X_MINIMAP;
	y -= MIN_Y_MINIMAP;
	if (x > 0 && x < (int)image->width && y > 0 && y < (int)image->height)
	{
		mlx_put_pixel(image, x, y, color);
	}
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	minimap_wrap_print(float x, float y, t_map *map, int32_t colour)
{
	if ((int)x < MAX_X_MINIMAP && (int)x > MIN_X_MINIMAP && \
	(int)y < MAX_Y_MINIMAP && (int)y > MIN_Y_MINIMAP)
		put_pixel_wrap(map->mini, (int)x, (int)y, colour);
}

uint32_t	mini_y(t_map *map, float y)
{
	float	rel;

	rel = y - map->player.y_coor;
	return (rel + get_mmap_centre_y());
}
