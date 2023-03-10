/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:18 by atito             #+#    #+#             */
/*   Updated: 2023/03/07 11:03:49 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	option_check(char **com, size_t *row, int *nl_flag)
{
	size_t	cnt;

	while (com[*row] && com[*row][0] == '-' && ft_strlen(com[*row]) > 1)
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

static int	print_com(char **com, size_t *row)
{
	while (com && com[*row])
	{
		ft_putstr_fd(com[*row], STDOUT_FILENO);
		*row += 1;
		if (com[*row])
			ft_putchar_fd(' ', STDOUT_FILENO);
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
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (SUCCESS);
	}
	option_check(com, &row, &nl_flag);
	if (print_com(com, &row) == FAILURE)
		return (FAILURE);
	if (nl_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
