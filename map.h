/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 15:58:00 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/13 17:24:08 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	*color_ceiling;
	char	*color_floor;
	int		**map_arr;
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

#endif
