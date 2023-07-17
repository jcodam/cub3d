/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 15:58:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/17 17:19:05 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_player
{
	int		map_x;
	int		map_y;
	int		start_direction;
}	t_player;

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

#endif
