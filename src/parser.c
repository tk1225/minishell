/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:12:53 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/28 23:26:48 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parser(char *line)
{
    char **res;

    res = lexer(line, " $");
    int i = 0;
    while (res[i])
    {
        printf("%s\n", res[i]);
        i ++;
    }
    return (res);
}