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

// int	executer(char **parsed_line, char **envp)
// {
// 	char	*command_path;

// 	command_path = ft_strjoin("/bin/", parsed_line[0]);
// 	if (execve(command_path, parsed_line, envp) == -1)
// 		exit(EXIT_SUCCESS);
// 	return (0);
// }

int	executer(char **parsed_line, char **envp)
{
	char *path = getenv("PATH");
    if (path == NULL) {
        perror("PATH environment variable not set");
        return 1;
    }

    size_t path_len = ft_strlen(path);
    char *path_copy = malloc(path_len + 1);
    strcpy(path_copy, path);

    char *dir = strtok(path_copy, ":");
    while (dir != NULL) {
        // size_t dir_len = strlen(dir);
        char exec_path[1024];
        snprintf(exec_path, sizeof(exec_path), "%s/%s", dir, parsed_line[0]);

        if (access(exec_path, X_OK) == 0) {
            // char *const args[] = {WC_EXECUTABLE, WC_OPTIONS, NULL};
            execve(exec_path, parsed_line, envp);
        }
        dir = strtok(NULL, ":");
    }

    perror("execve failed");
    return 1;
	return (0);
}



int	exec_recursion(t_tree *tree, char **envp)
{
	//pipe見つけたら左コマンド用にforkして子プロセスで
	//execveして標準出力をpipeで親プロセスの標準入力で受け取る。
	// (void)tree;
	// (void)envp;

	int pipefd[2];
	if (pipe(pipefd) == -1)
		return (1);
	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		//tree->leftがコマンドだったらexecve
		//tree->left pipeだったらさいき
		executer(tree->left->com, envp);
		// execve(ft_strjoin("/bin/", tree->left->com[0]), tree->left->com, envp);
		// execlp("echo", "echo", "test2", NULL);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		//tree->leftがコマンドだったらexecve
		//tree->left pipeだったらさいき
		executer(tree->right->com, envp);
		// execve(ft_strjoin("/usr/bin/", tree->right->com[0]), tree->right->com, envp);
		// execlp("wc", "wc", "-l", NULL);
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
