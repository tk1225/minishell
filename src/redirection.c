#include "minishell.h"

int handle_redirect(char *target_filename, int stdfd, int append_flag)
{
	int fd;

	if (stdfd == WRITE)
	{
		if (append_flag == 1)
			fd = open(target_filename, O_RDWR | O_CREAT | O_APPEND);
		else
			fd = open(target_filename, O_RDWR | O_CREAT | O_TRUNC);
	}
	else
		fd = open(target_filename, O_RDWR | O_CREAT);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	int new_fd = dup(fd);
	if (new_fd == -1)
	{
		perror("dup");
		return (1);
	}
	close(stdfd);
	if (dup2(new_fd, stdfd) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(new_fd);
	close(fd);
	return (new_fd);
}
