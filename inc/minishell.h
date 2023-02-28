#ifndef MINISHELL_H
# define MINISHELL_H

# define IN_QUOTE -1
# define OUT_QUOTE 1

# define SUCCESS 1
# define FAILURE 0

# define WRITE 1
# define READ 0

# define NEW 0
# define APPEND 1

# define PATH_SIZE 512

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <err.h>
# include <fcntl.h>
# include <sys/stat.h>
#include <errno.h>

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

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*value;
}	t_env;

//lexer
char	**lexer(char const *s);
void	free_lst(char **lst);

//parser
t_tree	**parser(char **res);

//expansion
void	expansion(char **com, t_env **env);

//fork
int		executer(char **com, t_env **env);
void	exec_tree(t_tree *tree, t_env **env);

//utils
void	*alloc_exit(size_t cnt, size_t size);
void	put_exit(char *str);
char	*join_three(const char *s1, const char *s2, const char *s3);

//exec
int		exec_recursion(t_tree *tree, t_env **env);
int		handle_pipe(t_tree *tree, t_env **env);
int		recognize_redirect(char **com);
int		handle_redirect(char *target_filename, int stdfd, int append_flag);
int		exec_check(char **com);
int		exec_builtin(t_tree *tree, t_env **env);
int		exec_set(char **com, t_env **env);
char	*getenvs(char *key, t_env **env);

//builtin
int		exec_cd(char **com, t_env **env);
int		exec_echo(char **com, t_env **env);
int		exec_env(char **com, t_env **env);
int		exec_exit(char **com, t_env **env);
int		exec_export(char **com, t_env **env);
int		exec_pwd(char **com, t_env **env);
int		exec_unset(char **com, t_env **env);

//builtin utils
int		add_env(char *com, t_env **env);

//delete
void	print_tree(t_tree *tree);

//syntax
int		syntax_check(t_tree *tree);

//signal
int		signal_check(void);
void	handle_signals(int sig);
int		read_heredoc(const char *delimiter);

#endif
