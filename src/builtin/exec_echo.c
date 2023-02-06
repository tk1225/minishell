#include "minishell.h"

int	exec_echo(char **com)
{
	size_t	cnt;
	int		nlflag;

	cnt = 1;
	nlflag = 1;
	if (ft_strncmp(com[cnt], "-n", ft_strlen(com[cnt])) == 0)
	{
		cnt += 1;
		nlflag = 0;
	}
	while (com[cnt])
	{
		ft_putstr_fd(com[cnt++], 1);
		if (com[cnt])
			ft_putchar_fd(' ', 1);
	}
	if (nlflag)
		ft_putchar_fd('\n', 0);
	return (1);
}
