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

void	exec_recursion(t_tree *tree)
{
	// if (tree->stat == COM)
	// {

	// }
	if (tree->stat = PIPE)
	{
	//pipe見つけたら左コマンド用にforkして子プロセスで
	//execveして標準出力をpipeで親プロセスの標準入力で受け取る。
		pid_t       pid;
		int         pipefd[2];
		char        buff[BUFFER_SIZE];
		int         status;
		int res =   pipe(pipefd);

		if (res == -1)
		{
			printf("%s","パイプ生成失敗");
			exit(EXIT_FAILURE);
		}
		//プロセス分岐
    	pid = fork();
		if (-1 == pid)
        err (EXIT_FAILURE, "can not fork");
		else if (0 == pid)
		{
			//子プロセス
			/* 使用しないwrite側はクローズ */
			close(pipefd[1]);
			/* パイプから読み込む */
			read(pipefd[0], &buff, BUFFER_SIZE);
			write(1, buff, 3);
			//read側をclose
			close(pipefd[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			/* 使用しないread側はクローズ */
			close(pipefd[0]);
			/* パイプに書き込む */
			write(pipefd[1], "testtest", 3);
			close(pipefd[1]);
			wait(&status);
			//ゾンビプロセス回避
			waitpid(pid, &status, 0);
		}

	}
	if (tree->stat = SEMICOL)
	{
	}


	//右コマンド用にforkして親プロセスのpipeから子プロセスの標準入力にわたす。
	//子プロセスの結果をpipeで親プロセスに渡す。
}
