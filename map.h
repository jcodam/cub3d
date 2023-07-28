/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 15:58:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/28 17:56:39 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "mlx/include/MLX42/MLX42.h"

typedef struct s_player
{
	int		map_x;
	int		map_y;
	int		start_direction;
	double	current_direction;
}	t_player;

typedef struct s_tile
{
	size_t		x;
	size_t		y;
	double		x_coor;
	double		y_coor;
	bool		is_open;
	int			width;
	int			depth;
	int			height;
	bool		is_player;
	bool		not_map;
}	t_tile;

typedef struct s_minimap
{
	mlx_image_t	*img;
	mlx_t		*mlx;
	// int		x_range;
	// int		y_range;
	// t_wall	*map_converted;
}	t_minimap;

typedef struct s_map
{
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*color_ceiling;
	char		*color_floor;
	char		**map_arr;
	t_player	player;
	t_tile		***tiles;
	t_minimap	*minimap;
	int			width;
	int			height;
}	t_map;

enum	e_map
{
	EOL=-1,
	EMPTY,	
	WALL,
	P_NORTH=10,
	P_SOUTH,
	P_WEST,
	P_EAST
};

int		fill_map(t_map *map, char const *path);
t_map	*mk_map(void);
t_map	*del_map(t_map *map);
int		write_map(t_map *map, int fd);

void	check_map(t_map *map);
void	map_exit(char *str);
void	_cub(char *arg);

int32_t	draw_map(t_map *map);
void	make_minimap(t_map *map, mlx_t *mlx);
int		check_mlx_error(mlx_t *mlx);

#endif
