/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:12:53 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/28 16:18:52 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parser(char *line)
{
    char **res;

    res = ft_split(line, ' ');
    // int i = 0;
    // while (res[i])
    // {
    //     printf("%s\n", res[i]);
    //     i ++;
    // }
    return (res);
}