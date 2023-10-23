/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:58:00 by jbax              #+#    #+#             */
/*   Updated: 2023/10/23 18:36:33 by avon-ben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "mlx/include/MLX42/MLX42.h"

typedef struct s_rays
{
	double	draw_x;
	double	draw_y;
	double	dist_x;
	double	dist_y;
	double	ray_x;
	double	ray_y;
	double	vert_x;
	double	vert_y;
	double	ray_angle;
	double	offset_x;
	double	offset_y;
	double	dist_v;
	double	dist_h;
}	t_rays;

typedef struct s_player
{
	int		map_x;
	int		map_y;
	double	x_coor;
	double	y_coor;
	double	rot;
	int		start_direction;
	double	x_angle;
	double	y_angle;
	double	length;
}	t_player;

typedef struct s_tile
{
	int			x;
	int			y;
	double		x_coor;
	double		y_coor;
	double		rel_x;
	double		rel_y;
	int			is_wall;
	int			height;
	int			is_player;
	int			not_map;
}	t_tile;

typedef struct s_png
{
	mlx_texture_t	*png_no;
	mlx_texture_t	*png_so;
	mlx_texture_t	*png_we;
	mlx_texture_t	*png_ea;
	int				color_ceiling;
	int				color_floor;
}	t_png;

typedef struct s_map
{
	char		*path_no;
	char		*path_so;
	char		*path_we;
	char		*path_ea;
	char		*color_ceiling;
	char		*color_floor;
	t_png		*png;
	char		**map_arr;
	t_player	player;
	t_tile		***tiles;
	t_rays		*rays;
	mlx_image_t	*img;
	mlx_image_t	*mini;
	int			is_mini;
	mlx_t		*mlx;
	int			width;
	int			height;
	int			stop;
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
int			fill_map(t_map *map, char const *path);
/* make's the struct with malloc*/
t_map		*mk_map(void);
/* delete's all the malloc't data in map returns 0*/
t_map		*del_map(t_map *map);
/* write's all map data */
int			write_map(t_map *map, int fd);
/* check's if map has walls where player can go and chars */
void		check_map(t_map *map);
/* writes string and exit function*/
void		map_exit(char *str);
/* checks if file has .cub */
int			_cub(char *arg);
/* return 0 if map is full 2 if only map is missing */
int			check_map_full(t_map *map);
/* checks the color string. checks
	if only numbers
	only 3 numbers
	number under 255 the max rgb value
	and changes multiple separators to only one */
char		*color_syntax(char *str);
void		draw_background(t_map *map);
void		wall_texture(t_map *map, double distence,
				int angle, double point_png);
void		mk_png(t_map *map);
int			check_png_full(t_map *map);
t_map		*del_png_s(t_map *map);
/* copys the png image pixeldata to img pixeldata 
on pixel position y x and are proteckted from going over or under screen size*/
void		image_to_image(mlx_image_t *img, mlx_image_t *png, int y, int x);
void		prep_map_syntax(t_map *map);

// drawing.c
void		put_pixel_wrap(mlx_image_t *image, int x, int y, uint32_t color);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		minimap_wrap_print(double x, double y, t_map *map, int32_t colour);
uint32_t	mini_y(t_map *map, double y);

//map_tiles.c
t_tile		*init_tile(size_t i, size_t j, t_map *map);
t_tile		***init_tiles(t_map *map, size_t j, size_t width, t_tile ***tiles);
int			make_tiles(t_map *map);

// minimap.c
void		draw_minimap(t_map *map);
void		mk_rel_vals(t_map *map);
void		init_direction(t_map *map);
void		make_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img);
int32_t		draw_map(t_map *map);

// minimap_tools.c
void		ft_draw_player(void *param);
double		fixang(double a);
void		init_rays(t_rays *rays);
int			close_mlx(mlx_t *mlx);

// temp_tools.c
void		print_tiles(t_map *map);

// tools.c
double		get_mmap_centre_x(void);
double		get_mmap_centre_y(void);
double		mini_rel_x(t_map *map, int i, int j);
double		mini_rel_y(t_map *map, int i, int j);
uint32_t	mini_x(t_map *map, double x);

// mmap_init.c
void		expand_walls(t_map *map, int i, int j);
void		convert_coordinates(t_map *map);
void		shade_box(t_map *map);
void		draw_box(t_map *map);
void		init_tile_part(t_tile *tile, size_t i, size_t j);

// rays.c
void		draw_line(t_map *map, double int_x, double int_y, int col);
int			cast_rays(t_map *map);

// rays_tools.c
int			move_to_next_point_h(t_map *map, int len);
int			move_to_next_point_v(t_map *map, int len);
void		set_straight_line(t_map *map, double Tan);
int			set_rays(t_map *map);

// rays_directions.c
void		vert_right(t_map *map, double Tan);
void		vert_left(t_map *map, double Tan);
void		hor_up(t_map *map, double Tan);
void		hor_down(t_map *map, double Tan);

// map_tiles.c
int			make_tiles(t_map *map);

// movement.c
void		mini_display(mlx_key_data_t keycode, void *param);
void		ft_move_player(void *param);
int			check_dir(t_map *map, size_t i, size_t j, double dir);
int			check_wall_pos(t_map *map, size_t pos_x, size_t pos_y);
void		move(t_map *map, double dir);

#endif