#include "minishell.h"
#include "exec.h"

int	executer(int argc, char **parsed_line, char **envp)
{
char	*command_path;
pid_t	pid;
int		status;

command_path = ft_strjoin("/bin/", parsed_line[0]);
(void)argc;
pid = fork();
if (-1 == pid)
	err (EXIT_FAILURE, "can not fork");
else if (0 == pid)
{
	//子プロセス
	if (execve(command_path, parsed_line, envp) == -1){}
		exit(EXIT_SUCCESS);
}
else
{
	//親プロセス
	wait(&status);
	//ゾンビプロセス回避
	waitpid(pid, &status, 0);
}
return (0);
}

void	exec_tree(t_tree *tree, char **envp)
{
	size_t k;

	k = 0;
	if (tree == NULL)
		return;
	exec_tree(tree->left, envp);
	printf("-----\n");
	if (tree->com)
		printf("this node\n");
	while (k < tree->len)
		printf("%s\n", tree->com[k++]);
	printf("-----\n");
	if (tree->com)
		executer(tree->len, tree->com, envp);
	exec_tree(tree->right, envp);
}
