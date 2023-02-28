#include "minishell.h"

extern	int g_status;

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	while (1)
	{
		if (g_status == 130)
			break ;
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0 || g_status == 130)
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
	close(fd);
	return (1);
}
