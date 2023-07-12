/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 15:22:40 by jbax          #+#    #+#                 */
/*   Updated: 2022/04/11 18:20:41 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t size1)
{
	long unsigned int	i;
	char				*star;

	i = 0;
	star = malloc(size1);
	if (star == NULL)
		return (0);
	while (i < size1)
	{
		star[i] = '\0';
		i++;
	}
	return (star);
}

void	ft_str_copy(char *dest, char *src, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		dest[i] = src[j];
		i++;
		if (src[j] != '\0')
			j++;
	}
}

int	ft_zero_free(char *buf)
{
	buf[0] = '\0';
	free(buf);
	return (-4);
}
