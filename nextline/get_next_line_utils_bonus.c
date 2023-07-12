/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 13:46:45 by jbax          #+#    #+#                 */
/*   Updated: 2022/04/15 12:52:28 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t size1)
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

char	*join(char *buf, char *temp, int *pi, int last)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (buf[i] != '\n' && buf[i] != '\0' && i != last)
		i++;
	if (buf[i] == '\n')
		*pi = i;
	if (buf[i] == '\0')
		*pi = -1;
	while (temp[j] != '\0')
		j++;
	dest = malloc(i + j + 2);
	if (dest == NULL)
		return (NULL);
	ft_str_copy(dest, temp, j);
	ft_str_copy(&dest[j], buf, i + 1);
	ft_str_copy(&dest[j + i + 1], "", 1);
	return (dest);
}