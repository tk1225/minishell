#include "minishell.h"

int	exec_echo(char **com, char **envp)
{
	size_t	row;
	size_t	cnt;
	int		nl_flag;

	(void)envp;
	row = 1;
	nl_flag = 1;
	if (!com[row])
		ft_putchar_fd('\n', 1);
	while (com[row][0] == '-')
	{
		cnt = 1;
		while (com[row][cnt] == 'n')
			cnt += 1;
		if (com[row][cnt])
			break ;
		row += 1;
		nl_flag = 0;
	}
	while (com[row])
	{
		ft_putstr_fd(com[row++], 1);
		if (com[row])
			ft_putchar_fd(' ', 1);
	}
	if (nl_flag)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
