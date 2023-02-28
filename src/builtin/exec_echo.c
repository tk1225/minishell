#include "minishell.h"

void	option_check(char **com, size_t *row, int *nl_flag)
{
	size_t	cnt;

	while (com[*row][0] == '-' && ft_strlen(com[*row]) > 1)
	{
		cnt = 1;
		while (com[*row][cnt] == 'n')
			cnt += 1;
		if (com[*row][cnt])
			break ;
		*row += 1;
		*nl_flag = 0;
	}
}

int	print_com(char **com, size_t *row)
{
	while (com[*row])
	{
		if (ft_putstr_fd(com[*row], 1) == -1)
			return (FAILURE);
		*row += 1;
		if (com[*row])
		{
			if (ft_putchar_fd(' ', 1) == -1)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	exec_echo(char **com, t_env **env)
{
	size_t	row;
	int		nl_flag;

	(void)env;
	row = 1;
	nl_flag = 1;
	if (!com[row])
	{
		if (ft_putchar_fd('\n', 1) == -1)
			return (FAILURE);
		return (SUCCESS);
	}
	option_check(com, &row, &nl_flag);
	if (print_com(com, &row) == FAILURE)
		return (FAILURE);
	if (nl_flag)
	{
		if (ft_putchar_fd('\n', 1) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
