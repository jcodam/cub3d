/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 14:51:40 by jbax          #+#    #+#                 */
/*   Updated: 2023/08/29 14:43:41 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft/libft.h"
#include "defines.h"

// static void	cpy_x_pixel(mlx_image_t *img, mlx_texture_t *png, unsigned int width, unsigned int height)
// {
// }

static void	texture_scale(mlx_image_t *img, mlx_texture_t *png, double width, double height)
{
	unsigned int	count;
	double			count2;
	double			count3;
	unsigned int	iii;
	double			www;
	// double	hhh;
	// int

	(void)width;
	(void)height;
	count = 0;
	www = ((width / png->width) * 1000);
	www = ((int)www % 1000);
	www = www / 1000;
	count2 = (double)png->width / width;
	count3 = (double)png->height / height;
	iii = 0;
	while (iii < height)
	{
		while (count < width)
		{
			ft_memcpy(img->pixels + (WIDTH * iii + count) * 4, png->pixels + \
				(int)(png->width * (int)(iii * count3) + count * count2) * 4,
				png->bytes_per_pixel);
			count++;
		}
		count = 0;
		iii++;
	}
}

static void	texture_test(t_map *map)
{
	mlx_texture_t	*png;
	// mlx_image_t		*img;

	ft_putnbr_fd(ft_strchr_set(map->path_no, "\n"), 1);
	ft_putendl_fd(map->path_no + 2, 1);
	png = mlx_load_png(map->path_no);
	if (!png)
		map_exit("error\npng didn't load\n");
	texture_scale(map->img, png, 64 * 4, 64 * 6);
	// img = mlx_texture_to_image(map->mlx, png);
	// if (!img)
	// 	map_exit("error\nimige didn't load\n");
	// mlx_image_to_window(map->mlx, img, 0, 64);
	// mlx_image_to_window(map->mlx, img, 64, 64);
	// mlx_image_to_window(map->mlx, img, 64, 0);
}

void	draw_background(t_map *map)
{
	int				pos_width;
	int				pos_height;
	int				floor;
	int				ceiling;

	ceiling = ft_pixel(52, 210, 240, 200);
	floor = ft_pixel(128, 83, 11, 200);
	pos_width = 0;
	pos_height = 0;
	ft_putendl_fd(map->path_no + 2, 1);
	while (pos_height != HEIGHT)
	{
		while (pos_width != WIDTH)
		{
			if (pos_height <= HEIGHT / 2)
				mlx_put_pixel(map->img, pos_width, pos_height, ceiling);
			else
				mlx_put_pixel(map->img, pos_width, pos_height, floor);
			pos_width++;
		}
		pos_width = 0;
		pos_height++;
	}
	texture_test(map);
}

	// static mlx_image_t		*img = NULL;
		// img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	// mlx_
	// mlx_image_to_window(map->mlx, img, 0, 0);
	// mlx_image_to_window(map->mlx, map->img, 0, 0);