#include "minishell.h"

int	exe_com(char **com, char **envp)
{
	char *path;

	path = getenv("PATH");
	if (path == NULL) {
		perror("PATH environment variable not set");
		return (1);
	}
	size_t path_len = ft_strlen(path);
	char *path_copy = malloc(path_len + 1);
	strcpy(path_copy, path);
	char *dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		char exec_path[1024];
		snprintf(exec_path, sizeof(exec_path), "%s/%s", dir, com[0]);
		if (access(exec_path, X_OK) == 0)
			execve(exec_path, com, envp);
		dir = strtok(NULL, ":");
	}
	perror("execve failed");
	return (0);
}

int	executer(char **com, char **envp)
{
	//comの中で< > を見つけたらそのあとをファイル名として扱う
	// < とその一つ後ろについては無視してコマンドを実行する
	// handle_redirect("sample.txt", WRITE, APPEND);
	// handle_redirect("sample.txt", READ);
	//comの変数展開
	ft_expansion_quote(com);
	ft_expansion_env(com);
	if (exec_set(com) == FAILURE)
		exe_com(com, envp);
	else
		exit(0);
	return (0);
}

int	exec_recursion(t_tree *tree, char **envp)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (tree->stat == COM)
			executer(tree->com, envp);
		handle_pipe(tree, envp);
	}
	waitpid(pid, NULL, 0);
	return(0);
}

//echo test | wc -l
//echo test | wc -l
