/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 13:10:18 by jbax          #+#    #+#                 */
/*   Updated: 2022/04/15 12:59:57 by jbax          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

char	*get_next_line(int fd);
void	*ft_calloc(size_t size1);
void	ft_str_copy(char *dest, char *src, size_t len);
int		ft_zero_free(char *buf);
char	*join(char *buf, char *temp, int *pi, int last);

#endif