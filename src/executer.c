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

static void shift_com(char **com, int i)
{
	while (com[i + 2])
	{
		free(com[i]);
		com[i] = com[i + 2];
		i++;
	}
	// free(com[i]);
	com[i] = NULL;
	// free(com[i + 1]);
	com[i + 1] = NULL;
}

int	executer(char **com, char **envp)
{
	int i;
	char *filename;
	
	i = 0;
	while (com[i])
	{
		if (ft_strncmp(com[i], "<<", 2) == 0)
		{
			// <<   を見つけた場合　次の文字列を識別子とする。
			//改行以降をDOCの内容とする。
			//改行と改行の間に識別子を見つけたらDOCはそこまでの内容をtmpfileに保存

			//handle_redirect("tmpfile", READ, NEW);で実行
			//ファイルとして保存し標準入力として渡す。
		}
		else if (ft_strncmp(com[i], ">>", 2) == 0)
		{
			filename = com[i + 1];
			handle_redirect(filename, WRITE, APPEND);
			shift_com(com, i);
		}
		else if (ft_strncmp(com[i], ">", 1) == 0)
		{
			filename = com[i + 1];
			handle_redirect(filename, WRITE, NEW);
			shift_com(com, i);
		}
		else if (ft_strncmp(com[i], "<", 1) == 0)
		{
			filename = com[i + 1];
			handle_redirect(filename, READ, NEW);
			shift_com(com, i);
		}
		i++;
	}

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
