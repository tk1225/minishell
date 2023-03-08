/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:11:44 by takuokam          #+#    #+#             */
/*   Updated: 2023/03/08 23:58:56 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

long long int	ft_strchr_len(const char *s, int c);
char			*ft_strdup_gnl(const char *s);
char			*ft_strjoin_bf_newline(char const *s1, char const *s2);
size_t			ft_strlen(const char *target);
char			*get_next_line(int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_free(char *s1, char *s2);

#endif