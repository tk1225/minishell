#include "minishell.h"

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

int handle_heredoc()
{
	int				fd;
	struct	stat	sb;
	int				ret;

	ret = lstat(".tmp.txt", &sb);
	if (ret == -1)
		return (1);
	fd = open(".tmp.txt", O_RDWR);
	if (fd == -1)
	{
		error_exit("open");
		return (1);
	}
	unlink(".tmp.txt");
	int new_fd = dup(fd);
	if (new_fd == -1)
	{
		error_exit("dup");
		return (1);
	}
	close(READ);
	if (dup2(new_fd, READ) == -1)
	{
		error_exit("dup2");
		return (1);
	}
	close(new_fd);
	close(fd);
	return (0);
}

int recognize_redirect(char **com)
{
	int i;
	char *filename;

	i = 0;
	while (com[i])
	{
		if (ft_strncmp(com[i], "<<", 3) == 0)
		{
			handle_heredoc();
			shift_com(com, i);
		}
		else if (ft_strncmp(com[i], ">>", 3) == 0)
		{
			filename = ft_strtrim(com[i + 1], "\"");
			if(handle_redirect(filename, WRITE, APPEND) == 1)
				exit(1);
			shift_com(com, i);
		}
		else if (ft_strncmp(com[i], ">", 2) == 0)
		{
			filename = ft_strtrim(com[i + 1], "\"");
			if(handle_redirect(filename, WRITE, NEW) == 1)
				exit(1);
			shift_com(com, i);
		}
		else if (ft_strncmp(com[i], "<", 2) == 0)
		{
			filename = ft_strtrim(com[i + 1], "\"");
			if(handle_redirect(filename, READ, NEW) == 1)
				exit(1);
			shift_com(com, i);
		}
		else
			i++;
	}
	return (0);
}

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
		fd = open(target_filename, O_RDWR);
	if (fd == -1)
	{
		error_exit("open");
		return (1);
	}
	int new_fd = dup(fd);
	if (new_fd == -1)
	{
		error_exit("dup");
		return (1);
	}
	close(stdfd);
	if (dup2(new_fd, stdfd) == -1)
	{
		error_exit("dup2");
		return (1);
	}
	close(new_fd);
	close(fd);
	return (0);
}
