/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:40:38 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/28 17:53:54 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *line = NULL;
    char **parsed_line = NULL;

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
        parsed_line = parser(line);
        executer(argc, parsed_line, envp);
        free(line);
    }
    printf("exit\n");
    return 0;
}

