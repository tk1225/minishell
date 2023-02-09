#include "minishell.h"

int	exec_echo(char **com)
{
	size_t	cnt;
	size_t	cnt2;
	int		nl_flag;

	cnt = 1;
	nl_flag = 1;
	if (!com[cnt])
		ft_putchar_fd('\n', 1);
	while (com[cnt][0] == '-')
	{
		cnt2 = 1;
		while (com[cnt][cnt2] == 'n')
			cnt2 += 1;
		if (com[cnt][cnt2])
			break ;
		cnt += 1;
		nl_flag = 0;
	}
	while (com[cnt])
	{
		ft_putstr_fd(com[cnt++], 1);
		if (com[cnt])
			ft_putchar_fd(' ', 1);
	}
	if (nl_flag)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
