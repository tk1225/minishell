#include "minishell.h"

pid_t	fork_wrapper(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		error_exit("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	dup_wrapper(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		error_exit("dup");
		exit(EXIT_FAILURE);
	}
	return (new_fd);
}

void	dup2_wrapper(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
	{
		error_exit("dup2");
		exit(EXIT_FAILURE);
	}
}
