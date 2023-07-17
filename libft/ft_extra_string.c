/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_extra_string.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 18:11:17 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/17 19:09:18 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrep(char *src, char *set, char target)
{
	int		n;

	n = 0;
	while (*src)
	{
		while (set[n])
		{
			if (set[n] == *src)
				*src = target;
			n++;
		}
		n = 0;
		src++;
	}
}

int	ft_strempty(char *src)
{
	int		n;
	int		index;

	index = 0;
	n = 0;
	while (src[index])
	{
		if (!ft_iswhite_space(src[index]))
			return (0);
		index++;
	}
	return (1);
}

int	ft_strinset(char *src, char *set)
{
	int		n;
	int		index;

	index = 0;
	n = 0;
	while (src[index])
	{
		while (set[n] != src[index])
		{
			if (!set[n])
				return (0);
			n++;
		}
		n = 0;
		index++;
	}
	return (1);
}

int	ft_strchr_set(char *src, char *set)
{
	int		n;
	int		index;

	index = 0;
	n = 0;
	while (src[index])
	{
		while (set[n])
		{
			if (set[n] == src[index])
				return (index);
			n++;
		}
		n = 0;
		index++;
	}
	return (-1);
}
