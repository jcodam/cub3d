/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mmap_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avon-ben <avon-ben@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 20:00:54 by avon-ben      #+#    #+#                 */
/*   Updated: 2023/08/23 13:42:33 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "defines.h"

void	expand_walls(t_map *map, int i, int j)
{
	float	x;
	float	y;
	float	start_x;
	float	start_y;

	x = mini_rel_x(map, i, j);
	y = mini_rel_y(map, i, j);
	start_x = x;
	start_y = y;
	while (x < (start_x + ((TILE_RAD * 2) - 1)))
	{
		while (y < (start_y + ((TILE_RAD * 2) - 1)))
		{
			minimap_wrap_print(x, y, map, ft_pixel(255, 0, 0, 255));
			y++;
		}
		y = start_y;
		x++;
	}
}

void	convert_coordinates(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map->tiles[i])
	{
		while (map->tiles[i][j])
		{
			map->tiles[i][j]->x_coor = ((j * (TILE_RAD * 2)));
			map->tiles[i][j]->y_coor = ((i * (TILE_RAD * 2)));
			if (map->tiles[i][j]->is_player)
			{
				map->player.x_coor = map->tiles[i][j]->x_coor;
				map->player.y_coor = map->tiles[i][j]->y_coor;
				init_direction(map);
			}
			j++;
		}
		j = 0;
		i++;
	}
	mk_rel_vals(map);
}

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
			put_pixel_wrap(map->img, x, y, \
			ft_pixel(255, 255, 255, 100));
			y++;
		}
		y = MIN_Y_MINIMAP;
		x++;
	}
}

void	draw_box(t_map *map)
{
	int	x;
	int	y;

	shade_box(map);
	x = (MIN_X_MINIMAP);
	y = (MIN_Y_MINIMAP);
	while (y < MAX_Y_MINIMAP)
	{
		put_pixel_wrap(map->img, x, y, ft_pixel(0, 0, 0, 255));
		put_pixel_wrap(map->img, (x + (MAX_X_MINIMAP - \
		MIN_X_MINIMAP)), y, ft_pixel(0, 0, 0, 255));
		y++;
	}
	y = (MIN_Y_MINIMAP);
	while (x < MAX_X_MINIMAP)
	{
		put_pixel_wrap(map->img, x, y, ft_pixel(0, 0, 0, 255));
		put_pixel_wrap(map->img, x, (y + (MAX_Y_MINIMAP - \
		MIN_Y_MINIMAP)), ft_pixel(0, 0, 0, 255));
		x++;
	}
}
