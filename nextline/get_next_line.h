/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 15:44:33 by jbax          #+#    #+#                 */
/*   Updated: 2023/07/14 18:15:36 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

char	*get_next_line(int fd);
char	*ft_calloc_gnl(size_t size1);
void	ft_str_copy(char *dest, char *src, size_t len);
int		ft_zero_free(char **buf);

#endif