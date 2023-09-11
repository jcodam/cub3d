/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:07:32 by jbax              #+#    #+#             */
/*   Updated: 2023/09/11 17:10:04 by jbax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft/libft.h"
#include "map.h"
#include "defines.h"

void	start_mapping(char *addr)
{
	t_map	*map;

	map = mk_map();
	fill_map(map, addr);
	if (!make_tiles(map))
		exit(1);
	prep_map_syntax(map);
	check_map(map);
	mk_png(map);
	draw_map(map);
	map = del_png_s(map);
	map = del_map(map);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		ft_putnbr_fd(argc, 1);
		ft_putendl_fd(FG_RED"Error\nyou forgot map input"FG_DEFAULT, 1);
		return (1);
	}
	fg_putstr_rgb_fd(argv[1], "45;255;45", 1);
	write(1, "\n", 1);
	_cub(argv[1]);
	start_mapping(argv[1]);
	return (0);
}
