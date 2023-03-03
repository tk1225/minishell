#include "minishell.h"

static void	shift_com(char **com, int i)
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

int	handle_heredoc(void)
{
	int				fd;
	struct stat		sb;
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
	if (dup2(fd, READ) == -1)
	{
		error_exit("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	recognize_redirect(char **com)
{
	int		i;
	int		res;
	char	*filename;

	i = 0;
	res = 2;
	while (com[i])
	{
		filename = ft_strtrim(com[i + 1], "\"");
		if (ft_strncmp(com[i], "<<", 2) == 0)
			res = handle_heredoc();
		else if (ft_strncmp(com[i], ">>", 2) == 0)
			res = handle_redirect(filename, WRITE, APPEND);
		else if (ft_strncmp(com[i], ">", 1) == 0)
			res = handle_redirect(filename, WRITE, NEW);
		else if (ft_strncmp(com[i], "<", 1) == 0)
			res = handle_redirect(filename, READ, NEW);
		free(filename);
		if (res == 1)
			exit(1);
		else if (res == 2)
			i ++;
		else if (res == 0)
			shift_com(com, i);
		res = 2;
	}
	return (0);
}

int	handle_redirect(char *target_filename, int stdfd, int append_flag)
{
	int	fd;

	if (stdfd == WRITE)
	{
		if (append_flag == 1)
			fd = open(target_filename, O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			fd = open(target_filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	else
		fd = open(target_filename, O_RDWR, 0666);
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
	if (dup2(fd, stdfd) == -1)
	{
		error_exit("dup2");
		return (1);
	}
	close(fd);
	return (0);
}
