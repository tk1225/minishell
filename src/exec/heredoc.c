/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:34:14 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/09 00:09:37 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	handle_heredoc_line(char *line, const char *delimiter, int fd)
{
	int	new_stdin_fd;

	if (line == NULL)
	{
		new_stdin_fd = open("/dev/tty", O_RDONLY);
		dup2(new_stdin_fd, STDIN_FILENO);
		if (g_status != 130)
			write(1, "\n", 1);
		return (0);
	}
	if (ft_strncmp(line, delimiter, \
		ft_strlen(delimiter)) == 0 || g_status == 130)
	{
		if (g_status == 130)
			g_status = 1;
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;
	int		flag;

	flag = 1;
	fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	while (flag)
	{
		set_signal_heredoc();
		write(2, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		flag = handle_heredoc_line(line, delimiter, fd);
	}
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (1);
}

int	handle_heredoc(void)
{
	int				fd;
	struct stat		sb;
	int				ret;

	if (g_status == 130)
	{
		unlink(".tmp.txt");
		return (1);
	}
	ret = lstat(".tmp.txt", &sb);
	if (ret == -1)
		return (1);
	fd = open(".tmp.txt", O_RDWR);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	unlink(".tmp.txt");
	if (close(READ) == -1)
		exit(EXIT_FAILURE);
	dup2_wrapper(fd, READ);
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (0);
}
