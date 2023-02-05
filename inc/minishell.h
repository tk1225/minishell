#ifndef MINISHELL_H
# define MINISHELL_H

# define IN_QUOTE 1
# define OUT_QUOTE -1

# define FAILURE 1

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <err.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define WRITE 1
# define READ 0

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	char			**com;
	size_t			len;
	int				stat;
}	t_tree;

typedef enum e_stat
{
	COM,
	PIPE,
	SEMICOL
}	t_stat;

//lexer
char	**lexer(char const *s);
void	free_lst(char **lst);

//parser
t_tree	**parser(char *line);

//fork
int	executer(char **parsed_line, char **envp);
void	exec_tree(t_tree *tree, char **envp);

//builtin
int		exec_pwd(void);

//utils
void	*alloc_exit(size_t cnt, size_t size);
void	put_exit(char *str);

//exec
int	exec_recursion(t_tree *tree, char **envp);

//delete
void	print_tree(t_tree *tree);

#endif
