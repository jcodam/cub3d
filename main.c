/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:07:32 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/17 19:00:20 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft/libft.h"
#include "map.h"

void	test(char *addr)
{
	t_map	*map;
	char	*temp;

	fg_putstr_rgb_fd(addr, "45;255;45", 1);
	write(1, "\n", 1);
	map = mk_map();
	fill_map(map, addr);
	temp = map->color_floor;
	map->color_floor = ft_strtrim(temp, "\n");
	free(temp);
	temp = map->color_ceiling;
	map->color_ceiling = ft_strtrim(temp, "\n");
	free(temp);
	ft_strrep(map->color_ceiling, ",.-", ';');
	ft_strrep(map->color_floor, ",.-", ';');
	fg_set_rgb_fd(map->color_ceiling, 1);
	fg_set_rgb_fd(map->color_floor, 1);
	if (map)
	{
		write_map(map, 1);
	}
	check_map(map);
	map = del_map(map);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		ft_putnbr_fd(argc, 1);
		ft_putendl_fd(FG_RED"error\nyou forgot map input"FG_DEFAULT, 1);
		return (1);
	}
	test(argv[1]);
	return (0);
}
	// system("leaks -q cub3D");
