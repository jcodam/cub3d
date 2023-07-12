/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:07:32 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/12 17:42:25 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft/libft.h"

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		ft_putnbr_fd(argc, 1);
		ft_putendl_fd(FG_RED"error\nyou forgot map input"FG_DEFAULT, 1);
		return (1);
	}
	if (argc == 3)
		fg_putstr_rgb_fd(argv[1], argv[2], 1);
	fg_putstr_rgb_fd(argv[1], "45;255;45", 1);
	return (0);
}
