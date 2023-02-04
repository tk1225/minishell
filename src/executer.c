#include "minishell.h"
#include "exec.h"

// void	exec_tree(t_tree *tree, char **envp)
// {
// 	size_t k;
// 	k = 0;
// 	if (tree == NULL)
// 		return;
// 	exec_tree(tree->left, envp);
// 	printf("-----\n");
// 	if (tree->com)
// 		printf("this node\n");
// 	while (k < tree->len)
// 		printf("%s\n", tree->com[k++]);
// 	printf("-----\n");
// 	if (tree->com)
// 		executer(tree->len, tree->com, envp);
// 	exec_tree(tree->right, envp);
// }

int	executer(char **parsed_line, char **envp)
{
	char	*command_path;

	command_path = ft_strjoin("/bin/", parsed_line[0]);
	printf("%s\n", command_path);
	if (execve(command_path, parsed_line, envp) == -1)
		exit(EXIT_SUCCESS);
	return (0);
}

int	exec_recursion(t_tree *tree, char **envp)
{
	//pipe見つけたら左コマンド用にforkして子プロセスで
	//execveして標準出力をpipeで親プロセスの標準入力で受け取る。
	int pipefd[2];
	(void)envp;
	if (pipe(pipefd) == -1)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	printf("pid1%d\n", pid1);
	if (pid1 == 0)
	{
		//child
		dup2(pipefd[1], STDOUT_FILENO);
		printf("%s\n", tree->left->com[0]);
		printf("%s\n", tree->left->com[1]);
		close(pipefd[0]);
		close(pipefd[1]);
		//tree->leftがコマンドだったらexecve
		//tree->left pipeだったらさいき
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
		// executer(tree->left->com, envp);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return 3;

	if (pid2 == 0)
	{
		//child
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		//tree->leftがコマンドだったらexecve
		//tree->left pipeだったらさいき
		execlp("grep", "grep", "icmp_seq=1", NULL);
		// executer(tree->right->com, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	//右コマンド用にforkして親プロセスのpipeから子プロセスの標準入力にわたす。
	//子プロセスの結果をpipeで親プロセスに渡す。
	return(0);
}

//echo test | wc -l
