/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:35:17 by atito             #+#    #+#             */
/*   Updated: 2022/11/03 13:08:11 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(const char *format, ...);
int		ft_print_char(char c);
int		ft_print_str(char *str);
char	*hex_num(unsigned int n);
char	*str_upper(char *str);
char	*ft_uitoa(unsigned int n);
char	*ft_ultoa(uintptr_t n);
int		ft_print_pointer(uintptr_t dst);

#endif
