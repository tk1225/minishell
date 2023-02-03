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
		line = readline("> ");
		if (line == NULL || ft_strlen(line) == 0)
			free(line);
		else
		{
			add_history(line);
			tree = parser(line);
			exec_tree(*tree, envp);
			free(line);
			// free_lst(parsed_line);
		}
	}
	printf("exit\n");
	return 0;
}
