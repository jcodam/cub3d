/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 12:50:56 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/14 18:04:37 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

static char	*buf_process(int fd, char **buf, char *dest, int *pi)
{
	int		ret;
	char	*temp;

	temp = dest;
	while (*pi < 0 && *pi > -2)
	{
		ft_str_copy(*buf, "\0", BUFFER_SIZE);
		ret = read(fd, *buf, BUFFER_SIZE);
		if (ret < 1)
		{
			ft_zero_free(buf);
			return (dest);
		}
		dest = join(*buf, temp, pi, ret);
		free(temp);
		if (dest == NULL)
			return (NULL);
		if (ret != BUFFER_SIZE && *pi == -1)
		{
			*pi = ft_zero_free(buf);
		}
		temp = dest;
	}
	return (dest);
}

static char	*buf_check(char *buf, int *pi)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = BUFFER_SIZE;
	while (buf[j] != '\n' && buf[j] != '\0')
		j += 1;
	if (buf[j] == '\n')
		dest = join(&buf[j + 1], "\0", pi, i);
	else
		dest = ft_calloc_gnl(1);
	if (!dest)
		return (NULL);
	if (*pi >= 0 && buf[*pi] == '\0')
		*pi = -1;
	if (*pi >= 0 && buf[*pi] != '\0')
	{
		j++;
		ft_str_copy(buf, &buf[j], i - j);
		ft_str_copy(&buf[i - j], "", j);
	}
	return (dest);
}

static char	*aloc_dest(int fd, char **buf)
{
	char	*dest;
	int		i;

	i = 0;
	dest = buf_check(*buf, &i);
	if (!dest)
	{
		free(*buf);
		return (NULL);
	}
	if (i < 0)
	{
		dest = buf_process(fd, buf, dest, &i);
	}
	if (!dest)
	{
		free(*buf);
		return (NULL);
	}
	return (dest);
}

char	*get_dest(char **buf, int fd)
{
	char		*dest;

	if (BUFFER_SIZE == 0)
		return (0);
	if (!*buf)
		*buf = ft_calloc_gnl(BUFFER_SIZE + 1);
	if (!*buf)
		return (NULL);
	dest = aloc_dest(fd, buf);
	if (!dest)
		return (NULL);
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*dest;
	int			i;

	i = 0;
	if (fd > OPEN_MAX || fd < 0)
		return (NULL);
	dest = get_dest(&buf[fd], fd);
	if (!dest)
		return (NULL);
	return (dest);
}
