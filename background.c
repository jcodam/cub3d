/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:51:40 by jbax              #+#    #+#             */
/*   Updated: 2023/09/09 17:11:41 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
// #include <float.h>
#include "color.h"
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
// 			ft_memcpy(img->pixels + (int)(WIDTH * iii + count) * 4,
// 				png->pixels + 
// 				(int)(png->width * (int)(iii * count3) + count * count2) * 4,
// 				png->bytes_per_pixel);
// 			count++;
// 		}
// 		count = 0;
// 		iii++;
// 	}
// }

static void	remove_newline(char **s)
{
	char	*new;

	new = ft_strtrim(*s, "\n");
	free(*s);
	*s = new;
}

void	prep_map_syntax(t_map *map)
{
	remove_newline(&map->path_ea);
	remove_newline(&map->path_we);
	remove_newline(&map->path_so);
	remove_newline(&map->path_no);
	remove_newline(&map->color_floor);
	remove_newline(&map->color_ceiling);
	ft_strrep(map->color_ceiling, ",.-", ';');
	ft_strrep(map->color_floor, ",.-", ';');
	map->color_ceiling = color_syntax(map->color_ceiling);
	map->color_floor = color_syntax(map->color_floor);
}

void	image_to_image(mlx_image_t *img, mlx_image_t *png, int y, int x)
{
	unsigned int	count;
	unsigned int	iii;

	if (x + png->width > WIDTH)
		x = WIDTH - png->width;
	if (y + png->height > HEIGHT)
		y = HEIGHT - png->height;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	iii = 0;
	while (iii < png->height)
	{
		count = 0;
		while (count < png->width)
		{
			ft_memcpy(img->pixels + (int)(WIDTH * (iii + y) + x + count)*4,
				png->pixels + \
				(int)(png->width * (int)(iii) + count) * 4,
				4);
			count++;
		}
		iii++;
	}
}

void	map_exit(char *str)
{
	fg_putstr_rgb_fd(str, "200;0;0", 1);
	exit(0);
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
}
