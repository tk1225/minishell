/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:40:20 by takuokam          #+#    #+#             */
/*   Updated: 2023/01/30 18:53:22 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define IN_QUOTE 1
# define OUT_QUOTE -1

char **parser(char *line);
int executer(int argc, char *argv[], char **envp);
char	**lexer(char const *s, char *c);

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <unistd.h>
#include <err.h>

#endif
