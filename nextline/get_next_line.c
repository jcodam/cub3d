/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:16:26 by jbax          #+#    #+#                 */
/*   Updated: 2022/04/15 12:59:12 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join(char *buf, char *temp, int *pi, int last)
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
			ft_zero_free(*buf);
			*buf = NULL;
			return (dest);
		}
		dest = join(*buf, temp, pi, ret);
		free(temp);
		if (dest == NULL)
			return (NULL);
		if (ret != BUFFER_SIZE && *pi == -1)
		{
			*pi = ft_zero_free(*buf);
			*buf = NULL;
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
		dest = ft_calloc(1);
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

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*dest;

	if (BUFFER_SIZE == 0)
		return (0);
	if (!buf)
		buf = ft_calloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	dest = aloc_dest(fd, &buf);
	if (!dest)
		return (NULL);
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}
