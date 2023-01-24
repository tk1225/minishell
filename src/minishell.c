/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:40:38 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/17 22:26:12 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *line = NULL;

    while (1)
    {
        line = readline("> ");
        if (line == NULL || ft_strlen(line) == 0)
        {
            free(line);
            break;
        }
        printf("line is '%s'\n", line);
        add_history(line);
        free(line);
    }
    printf("exit\n");
    return 0;
}