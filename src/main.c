#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		// write(1, "catch!\n", 7);
		// rl_on_new_line();
		// rl_redisplay();
		write(1, "\n", 1);
		rl_redisplay();
		// rl_replace_line("\n", 0);
	}
}

int	set_signal()
{
	// ◦ ctrl-C displays a new prompt on a new line.
	// ◦ ctrl-D exits the shell.
	// ◦ ctrl-\ does nothing.
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, &handle_signal);
	return (1);
}

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);

	while (1)
	{
		// set_signal();
		line = readline("");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		//次の行からがHEREDOCの内容
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// (void)envp;
	int status;
	char *line = NULL;
	t_tree **tree;

	while (1)
	{
		// test用
		rl_outstream = stderr;
		set_signal();
		line = readline("> ");
		if (line == NULL)
			break;
		if (line == NULL || ft_strlen(line) == 0)
			free(line);
		else
		{
			char **res;
			add_history(line);
			res = lexer(line);
			size_t	cnt;
			char *delimiter;
			cnt = 0;
			// int d_quote = -1;
			// int s_quote = -1;
			while (res[cnt])
			{
				// if (ft_strnstr(res[cnt], "<<", ft_strlen(line)))
				// printf("res%s\n",res[cnt]);
				if (ft_strncmp(res[cnt], "<<", 2) == 0)
				{
					delimiter = res[cnt + 1];
					// printf("deli%s\n",delimiter);
					// write(1, &delimiter, 4);
					if (delimiter == NULL)
						exit(2);
					read_heredoc(delimiter);
				}
				cnt += 1;
			}
			tree = parser(res);
			if (syntax_check(*tree) > 0)
			{
				perror("syntax error");
				status = 2;
				exit(2);
			}
			else
			{
				status = exec_recursion(*tree, envp);
			}
			// print_tree(*tree);
			// printf("子プロセスの終了ステータス: %d\n", WEXITSTATUS(status));
			free(line);
		}
	}
	exit(WEXITSTATUS(status));
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks minishell");
// }
