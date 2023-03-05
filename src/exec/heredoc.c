/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:34:14 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 11:04:45 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	int g_status;

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	while (1)
	{
		set_signal_heredoc();
		line = readline("heredoc> ");
		if (line == NULL)
		{
			int new_fd = open("/dev/tty", O_RDONLY);
			dup2(new_fd, STDIN_FILENO);
			break;
		}
		if (ft_strncmp(line, delimiter, \
		ft_strlen(delimiter)) == 0 || g_status == 130)
		{
			if (g_status == 130)
				g_status = 1;
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
	return (1);
}
