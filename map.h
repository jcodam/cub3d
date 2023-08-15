/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 15:58:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/08/15 15:29:05 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "mlx/include/MLX42/MLX42.h"

typedef struct s_rays
{
	int		mx;
	int		my;
	float	ray_x;
	float	ray_y;
	float	vector_x;
	float	vector_y;
	float	offset_x;
	float	offset_y;
	float	dist_V;
	float	dist_H;
	int		dof;


}	t_rays;

typedef struct s_player
{
	int		map_x;
	int		map_y;
	float	x_coor;
	float	y_coor;
	int		rotation;
	int		start_direction;
	float	x_angle;
	float	y_angle;
	float	length;
}	t_player;

typedef struct s_tile
{
	int			x;
	int			y;
	float		x_coor;
	float		y_coor;
	float		rel_x;
	float		rel_y;
	bool		is_open;
	int			width;
	int			depth;
	int			height;
	bool		is_player;
	bool		not_map;
}	t_tile;

// typedef struct s_minimap
// {
// 	mlx_image_t	*img;
// 	mlx_t		*mlx;
// }	t_minimap;

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
	// t_minimap	*minimap;
	t_rays		*rays;
	mlx_image_t	*img;
	mlx_t		*mlx;
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
	P_EAST,
	FLOOR,
	CEILING
};

/*try's to fill te struct with all his data */
int		fill_map(t_map *map, char const *path);
/* make's the struct with malloc*/
t_map	*mk_map(void);
/* delete's all the malloc't data in map returns 0*/
t_map	*del_map(t_map *map);
/* write's all map data */
int		write_map(t_map *map, int fd);
/* check's if map has walls where player can go and chars */
void	check_map(t_map *map);
/* writes string and exit function*/
void	map_exit(char *str);
/* checks if file has .cub */
void	_cub(char *arg);
/* return 0 if map is full 2 if only map is missing */
int		check_map_full(t_map *map);
/* checks the color string. checks
	if only numbers
	only 3 numbers
	number under 255 the max rgb value
	and changes multiple separators to only one */
char	*color_syntax(char *str);

// minimap.c
int32_t	draw_map(t_map *map);
void	make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img);
int		check_mlx_error(mlx_t *mlx, t_map *map);

void	draw_line(t_map *map, float dir_x, float dir_y);
void	minimap_wrap_print(float x, float y, t_map *map, int32_t colour);
void	put_pixel_wrap(mlx_image_t *image, int x, int y, uint32_t color);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void	mk_rel_vals(t_map *map);
void	init_direction(t_map *map);

// temp_tools.c
void	streight_line(t_map *map, float dir_x, float dir_y);
void	print_tiles(t_map *map);

// tools.c
float	get_mmap_centre_x(void);
float	get_mmap_centre_y(void);
float	mini_rel_x(t_map *map, int i, int j);
float	mini_rel_y(t_map *map, int i, int j);
int		mini_x(float x);
int		mini_y(float y);

// mmap_init.c
void	expand_walls(t_map *map, int i, int j);
void	convert_coordinates(t_map *map);
void	shade_box(t_map *map);
void	draw_box(t_map *map);

#endif