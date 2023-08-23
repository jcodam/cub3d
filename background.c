/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   background.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 14:51:40 by jbax          #+#    #+#                 */
/*   Updated: 2023/08/23 17:09:03 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft/libft.h"
#include "defines.h"

// static void	texture_test(t_map *map)
// {
// 	mlx_texture_t	*png;
// 	mlx_image_t		*img;
// 	// mlx_texture_t	*png2;
// 	// mlx_image_t		*img2;
// 	// mlx_texture_t	*png3;
// 	// mlx_image_t		*img3;
// 	// FILE			*test;

// 	ft_putnbr_fd(ft_strchr_set(map->path_no, "\n"), 1);
// 	ft_putendl_fd(map->path_no + 2, 1);
// 	png = mlx_load_png(map->path_no);
// 	if (!png)
// 		map_exit("error\npng didn't load\n");
// 	// png2 = mlx_load_png(map->path_so);
// 	// if (!png2)
// 	// 	map_exit("error\npng didn't load\n");
// 	// png3 = mlx_load_png(map->path_ea);
// 	// if (!png3)
// 	// 	map_exit("error\npng didn't load\n");
// 	img = mlx_texture_to_image(map->mlx, png);
// 	if (!img)
// 		map_exit("error\nimige didn't load\n");
// 	for (int i = 0; i < 64 ; i++)
// 	{
// 		ft_memcpy(map->img->pixels + (WIDTH * i) * 4, img->pixels + (64 * i) * 4, 64 * 4);

// 	}
// 	// printf("png : width %d -- height %d -- pixel %s\n", png->width, png->height, png->pixels);
// 	// png->height = (uint32_t)100;
// 	// png->width = (uint32_t)100;
// 	// img2 = mlx_texture_to_image(map->mlx, png2);
// 	// if (!img2)
// 	// 	map_exit("error\nimige2 didn't load\n");
// 	// img3 = mlx_texture_to_image(map->mlx, png3);
// 	// if (!img3)
// 	// 	map_exit("error\nimige3 didn't load\n");
// 	mlx_image_to_window(map->mlx, img, 0, 64);
// 	// mlx_image_to_window(map->mlx, img2, 0, 100);
// 	// mlx_image_to_window(map->mlx, img3, 100, 0);

// }

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
	// texture_test(map);
}

	// static mlx_image_t		*img = NULL;
		// img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	// mlx_
	// mlx_image_to_window(map->mlx, img, 0, 0);
	// mlx_image_to_window(map->mlx, map->img, 0, 0);