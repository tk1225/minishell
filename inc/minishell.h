#ifndef MINISHELL_H
# define MINISHELL_H

# define FAILURE 0
# define SUCCESS 1
# define NONE 2

# define READ 0
# define WRITE 1

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
typedef enum e_stat
{
	COM,
	PIPE
}	t_stat;

typedef enum e_quote
{
	IN_SQUOTE,
	IN_DQUOTE,
	OUT_QUOTE
}	t_quote;

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	char			**com;
	size_t			len;
	int				stat;
}	t_tree;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*value;
}	t_env;

//parser
char	**lexer(char *str);
t_tree	**parser(char **res);
void	expansion(char **com, t_env **env);
char	*next_dollar(t_env **env, char **str, char *prm);

//parser utils
int		judge_quote(int *quote, char c);
void	judge_char(char *c, int *quote, size_t *len);

//fork
int		executer(char **com, t_env **env);
void	exec_tree(t_tree *tree, t_env **env);

//free
void	free_lst(char **lst);
void	free_tree(t_tree *tree);
void	free_env(t_env *env);

//utils
void	*alloc_exit(size_t cnt, size_t size);
char	*join_three(const char *s1, const char *s2, const char *s3);
void	error_exit(char *str);
char	*get_env(char *key, t_env **env);
int		ch_dir(char *path);
pid_t	fork_wrapper(void);
int		dup_wrapper(int fd);
void	dup2_wrapper(int fd, int fd2);

//exec
int		exec_recursion(t_tree *tree, t_env **env);
int		handle_pipe(t_tree *tree, t_env **env, int pipe_count);
int		recognize_redirect(char **com);
int		handle_redirect(char *target_filename, int stdfd, int append_flag);
int		builtin_check(char **com);
int		exec_builtin(t_tree *tree, t_env **env);
int		builtin_set(char **com, t_env **env);

//pipe
int		count_pipe(t_tree *tree);
void	close_pipe(int pipe_count, int pipefd[4096][2]);
int		wait_pipeline(pid_t last_pid);
void	init_pipe(int pipe_count, int pipefd[4096][2]);
void	cat_pipe(int pipe_count, int pipefd[4096][2], int i);
int		exec_pipe(t_tree *tree, t_env **envp);
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
int		put_env(t_env *env);
t_env	*make_env(char c);
int		add_back_env(t_env *env, char *key, char *value);
void	bubble_sort(char **arr);

//syntax
int		syntax_check(t_tree *tree);

//signal
int		signal_check(void);
int		read_heredoc(const char *delimiter);
void	set_signal_read(void);
void	set_signal_run(void);
#endif
