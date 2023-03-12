/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:34:14 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/12 19:09:11 by takumasaoka      ###   ########.fr       */
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
		return (0);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
	{
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

static char	*handle_env_in_heredoc(char *line, t_env **env)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if (line[i] == '$')
			expansion_env(env, &tmp, line, i + 1);
		i++;
	}
	if (tmp != NULL)
	{
		free(line);
		line = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	return (line);
}

int	read_heredoc(const char *delimiter, t_env **env)
{
	char	*line;
	int		fd;
	int		flag;

	flag = 1;
	fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	while (flag)
	{
		g_status = 0;
		set_signal_heredoc();
		write(2, "> ", 3);
		line = get_next_line(STDIN_FILENO);
		if (line != NULL)
			line = handle_env_in_heredoc(line, env);
		flag = handle_heredoc_line(line, delimiter, fd);
	}
	close_wrapper(fd);
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
		return (0);
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
