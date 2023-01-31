#ifndef MINISHELL_H
# define MINISHELL_H

# define IN_QUOTE 1
# define OUT_QUOTE -1

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <err.h>

//lexer
char	**lexer(char const *s);
void	free_lst(char **lst);

//parser
char	**parser(char *line);

//fork
int		executer(int argc, char *argv[], char **envp);
int		exec_pwd(void);

#endif
