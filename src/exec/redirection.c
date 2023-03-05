/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:50:17 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 12:50:18 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	shift_com(char **com, int i)
{
	free(com[i]);
	free(com[i + 1]);
	while (com[i + 2])
	{
		com[i] = com[i + 2];
		i++;
	}
	com[i] = NULL;
	com[i + 1] = NULL;
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

static int	redirect_fork(char	*filename, char **com, int i, int res)
{
	if (ft_strncmp(com[i], "<<", 3) == 0)
		res = handle_heredoc();
	else if (ft_strncmp(com[i], ">>", 3) == 0)
		res = handle_redirect(filename, WRITE, APPEND);
	else if (ft_strncmp(com[i], ">", 2) == 0)
		res = handle_redirect(filename, WRITE, NEW);
	else if (ft_strncmp(com[i], "<", 2) == 0)
		res = handle_redirect(filename, READ, NEW);
	return (res);
}

int	recognize_redirect(char **com)
{
	int		i;
	int		res;
	char	*filename;
	char	*path;

	i = 0;
	res = 2;
	while (com[i])
	{
		path = ft_strtrim(com[i + 1], "\"");
		filename = get_absolute_path(path);
		free(path);
		res = redirect_fork(filename, com, i, res);
		free(filename);
		if (res == 1)
			return (1);
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
		perror("open");
		return (1);
	}
	if (close(stdfd) == -1)
		exit(EXIT_FAILURE);
	dup2_wrapper(fd, stdfd);
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (0);
}
