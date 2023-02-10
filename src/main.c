#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
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
			// print_tree(*tree);
			exec_recursion(*tree, envp);
			free(line);
		}
	}
	exit(0);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks minishell");
// }
