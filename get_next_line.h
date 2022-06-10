/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngmki <youngmki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 16:32:46 by youngmki          #+#    #+#             */
/*   Updated: 2021/07/23 19:23:22 by youngmki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char		*get_next_line(int fd);
size_t		gnl_strlen(const char *s);
int			gnl_strchr_i(const char *s, int c);
size_t		gnl_strlcpy(char *dst, const char *src, size_t size);
char		*gnl_substr(const char *s, unsigned int start, size_t len);
size_t		gnl_strlcat(char *dst, const char *src, size_t size);
char		*gnl_shrink_buffer(char *buf, char *line);
char		*gnl_expand_buffer(char *buf, int fd);
char		*gnl_newread(int fd);
#endif
