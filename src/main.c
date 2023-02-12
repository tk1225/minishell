#include "minishell.h"

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
			add_history(line);
			tree = parser(line);
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
