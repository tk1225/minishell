#include "minishell.h"

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	// int		pipefd[2];

	// if (pipe(pipefd) < 0)
	// 	perror("pipe");
	// int pid1 = fork();
	// if (pid1 < 0)
	// 	return (2);
	// if (pid1 == 0)
	// {
	// 	dup2(pipefd[WRITE], STDOUT_FILENO);
	// 	close(pipefd[0]);
	// 	close(pipefd[1]);
		while (1)
		{

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
			// dprintf(pipefd[1], "%s\n", line);
			// printf("%s\n", line);
			free(line);
		}
		close(fd);
		// exit(0);
	// printf("input_is:%s\n", line);
	// }
	// dup2(pipefd[READ], STDIN_FILENO);
	// close(pipefd[0]);
	// close(pipefd[1]);
	// waitpid(pid1, NULL, 0);
	// exit(0);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	int status;
	char *line = NULL;
	t_tree **tree;

	while (1)
	{
		// test用
		rl_outstream = stderr;
		line = readline("> ");
		// line = readline("> ");
		if (line == NULL || ft_strlen(line) == 0)
		{
			free(line);
			//test用にbreak
			break;
		}
		else
		{
			char **res;
			add_history(line);
			res = lexer(line);
			size_t	cnt;
			char *delimiter;
			// int pipefd;
			cnt = 0;
			while (res[cnt])
			{
				// printf("%s\n", res[cnt]);
				if (ft_strnstr(res[cnt], "<<", ft_strlen(line)))
				{
					// write(1,"ab\n",3);
					delimiter = res[cnt + 1];
					printf("deli is %s\n", delimiter);
					// pipefd = read_heredoc(delimiter);
					read_heredoc(delimiter);
					// close(pipefd);
					break;

				}
				cnt += 1;
			}
			tree = parser(res);
			// print_tree(*tree);
			status = exec_recursion(*tree, envp);
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
