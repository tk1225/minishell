#include "minishell.h"

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
	
	set_signal();
	// rl_event_hook;
	while (1)
	{
		// test用
		rl_outstream = stderr;
		// rl_catch_signals = 0;
		
		// rl_event_hook = set_signal();
		line = readline("$ ");
		if (line == NULL)
			break;
		if (ft_strlen(line) > 0)
		{
			char **res;
			add_history(line);
			res = lexer(line);
			size_t	cnt;
			char *delimiter;
			cnt = 0;
			while (res[cnt])
			{
				// printf("res%s\n",res[cnt]);
				if (ft_strncmp(res[cnt], "<<", 2) == 0)
				{
					delimiter = res[cnt + 1];
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
			rl_on_new_line();
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
