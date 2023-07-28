/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 14:36:35 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/28 16:27:10 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft/libft.h"

static int	check_valid_char(t_map *map, int x, int y, int *p_count)
{
	if (map->map_arr[y][x] == '1')
		return (1);
	if (map->map_arr[y][x] == '0')
		return (1);
	if (map->map_arr[y][x] == ' ')
		return (1);
	if (map->map_arr[y][x] == 'N' || map->map_arr[y][x] == 'E' || 
			map->map_arr[y][x] == 'W' || map->map_arr[y][x] == 'S')
	{
		*p_count += 1;
		map->player.map_x = x;
		map->player.map_y = y;
		if (map->map_arr[y][x] == 'N')
			map->player.start_direction = P_NORTH;
		if (map->map_arr[y][x] == 'E')
			map->player.start_direction = P_EAST;
		if (map->map_arr[y][x] == 'S')
			map->player.start_direction = P_SOUTH;
		if (map->map_arr[y][x] == 'W')
			map->player.start_direction = P_WEST;
		return (1);
	}
	return (0);
}

// static int	walk_route(char **route, int x, int y)
// {
// 	int	test_outcome;

// 	test_outcome = 0;
// 	if (!route[y][x] || !route[y + 1] || y == 0 || x == 0)
// 		return (1);
// 	if (route[y][x] == ' ' || route[y][x] == '\n')
// 		return (1);
// 	if (ft_strlen(route[y + 1]) < (unsigned)x || 
//		ft_strlen(route[y - 1]) < (unsigned)x)
// 		return (1);
// 	route[y][x] = '2';
// 	if (route[y - 1][x] != '1' && route[y - 1][x] != '2')
// 		test_outcome = walk_route(route, x, y - 1);
// 	if (route[y][x - 1] != '1' && route[y][x - 1] != '2')
// 		test_outcome = walk_route(route, x - 1, y);
// 	if (route[y][x + 1] != '1' && route[y][x + 1] != '2')
// 		test_outcome = walk_route(route, x + 1, y);
// 	if (route[y + 1][x] != '1' && route[y + 1][x] != '2')
// 		test_outcome = walk_route(route, x, y + 1);
// 	return (test_outcome);
// }
static int	walk_route(char **route, int x, int y)
{
	if (!route[y] || !route[y][x] || y < 0 || x < 0)
		return (1);
	if (route[y][x] == ' ' || route[y][x] == '\n')
		return (1);
	if (route[y][x] == '1' || route[y][x] == '2')
		return (0);
	if (!route[y + 1] || !route[y][x] || !y || x <= 0)
		return (1);
	if (ft_strlen(route[y + 1]) < (unsigned)x || 
		ft_strlen(route[y - 1]) < (unsigned)x)
		return (1);
	route[y][x] = '2';
	if (walk_route(route, x, y - 1))
		return (1);
	if (walk_route(route, x - 1, y))
		return (1);
	if (walk_route(route, x, y + 1))
		return (1);
	if (walk_route(route, x + 1, y))
		return (1);
	return (0);
}

static void	map_route(t_map *map)
{
	char	**test_route;

	test_route = ft_arrdup_c(map->map_arr, ft_arrlen_c(map->map_arr));
	if (!test_route)
		map_exit("Error\nmalloc failed\n");
	if (walk_route(test_route, map->player.map_x, map->player.map_y))
		map_exit("Error\ncan exit the map\n");
	ft_putarrs_fd(test_route, 1);
	ft_arrclear_c(test_route, ft_arrlen_c(test_route));
}
	// if (cep->map_p != cep->map_c)
	// 	map_exit("Error\ncan't collect all the sluge\n");

void	check_map(t_map *map)
{
	int		x;
	int		y;
	int		p_count;

	p_count = 0;
	x = 0;
	y = 0;
	while (map->map_arr[y])
	{
		while (map->map_arr[y][x] && map->map_arr[y][x] != '\n')
		{
			if (!check_valid_char(map, x, y, &p_count))
				map_exit("Error\ninvalid chars in map\n only"
					" 1,0,N,W,E,S and spaces are allowed\n");
			x++;
		}
		x = 0;
		y++;
	}
	if (p_count != 1)
		map_exit("Error\nin map\n exactly one player can/must be present\n");
	map_route(map);
}
