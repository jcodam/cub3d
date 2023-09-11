/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:37:50 by avon-ben          #+#    #+#             */
/*   Updated: 2023/09/11 13:12:41 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"

void	put_pixel_wrap(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		mlx_put_pixel(image, x - MIN_X_MINIMAP, y - MIN_Y_MINIMAP, color);
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
