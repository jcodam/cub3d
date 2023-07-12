/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 16:14:34 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/12 16:48:56 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "color.h"

void	fg_putstr_rgb_fd(char *str, char *rgb, int fd)
{
	char	*new;

	new = ft_strjoinx(5, "\e[38;2;", rgb, "m", str, FG_DEFAULT);
	write(fd, new, ft_strlen(new));
	free(new);
}

void	bg_putstr_rgb_fd(char *str, char *rgb, int fd)
{
	char	*new;

	new = ft_strjoinx(5, "\e[48;2;", rgb, "m", str, FG_DEFAULT);
	write(fd, new, ft_strlen(new));
	free(new);
}

void	fbg_putstr_rgb_fd(char *str, char *f_rgb, char *b_rgb, int fd)
{
	char	*new;

	new = ft_strjoinx(8, "\e[38;2;", f_rgb, "m", "\e[48;2;",
			b_rgb, "m", str, FG_DEFAULT);
	write(fd, new, ft_strlen(new));
	free(new);
}

void	fg_set_rgb_fd(char *rgb, int fd)
{
	char	*new;

	new = ft_strjoinx(3, "\e[38;2;", rgb, "m");
	write(fd, new, ft_strlen(new));
	free(new);
}

void	bg_set_rgb_fd(char *rgb, int fd)
{
	char	*new;

	new = ft_strjoinx(3, "\e[48;2;", rgb, "m");
	write(fd, new, ft_strlen(new));
	free(new);
}
