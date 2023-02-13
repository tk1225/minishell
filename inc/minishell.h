#ifndef MINISHELL_H
# define MINISHELL_H

# define IN_QUOTE 1
# define OUT_QUOTE -1

# define FAILURE 0
# define SUCCESS 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define WRITE 1
# define READ 0

# define NEW 0
# define APPEND 1

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "exec.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <err.h>
# include <fcntl.h>

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
	PIPE
}	t_stat;

//lexer
char	**lexer(char const *s);
void	free_lst(char **lst);

//parser
t_tree	**parser(char **res);

//expansion
void	ft_expansion_dquote(char **com);
void	ft_expansion_squote(char **com);
void	ft_expansion_env(char **com);

//fork
int		executer(char **com, char **envp);
void	exec_tree(t_tree *tree, char **envp);

//utils
void	*alloc_exit(size_t cnt, size_t size);
void	put_exit(char *str);
char	*str_join_three(const char *s1, const char *s2, const char *s3);

//exec
int		exec_recursion(t_tree *tree, char **envp);
int		handle_pipe(t_tree *tree, char **envp);
int		recognize_redirect(char **com);
int		handle_redirect(char *target_filename, int stdfd, int append_flag);

//delete
void	print_tree(t_tree *tree);

//syntax
int		syntax_check(t_tree *tree);

#endif
