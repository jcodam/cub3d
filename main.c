/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:07:32 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/13 17:34:37 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft/libft.h"
#include "map.h"
int	main(int argc, char *argv[])
{
	t_map *map;

	if (argc < 2)
	{
		ft_putnbr_fd(argc, 1);
		ft_putendl_fd(FG_RED"error\nyou forgot map input"FG_DEFAULT, 1);
		return (1);
	}
	if (argc == 3)
		fg_putstr_rgb_fd(argv[1], argv[2], 1);
	fg_putstr_rgb_fd(argv[1], "45;255;45", 1);
	map = mk_map();
	fill_map(map, argv[1]);
	if (map)
		fg_putstr_rgb_fd(map->path_no, "45;255;45", 1);
	map = del_map(map);
	return (0);
}
