/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:33 by atito             #+#    #+#             */
/*   Updated: 2023/03/10 18:27:41 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_overflow_checker(const char *str, long res, int i, int minus)
{
	if (minus == 0)
	{
		if (((res > LONG_MAX / 10) && (str[i + 1] != '\0')) || \
		((res == LONG_MAX / 10) && (str[i + 1] >= '8')))
			return (1);
	}
	else
	{
		if (((res > LONG_MAX / 10) && (str[i + 1] != '\0')) || \
		((res == LONG_MAX / 10) && (str[i + 1] >= '9')))
			return (-1);
	}
	return (0);
}

static	int	ft_checker_helper(const char *str, long res, int i, int minus)
{
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (FAILURE);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res + str[i] - '0';
		if (ft_overflow_checker(str, res, i, minus) == 1)
			return (FAILURE);
		else if (ft_overflow_checker(str, res, i, minus) == -1)
			return (FAILURE);
		res *= 10;
		i++;
	}
	if (!(str[i] == '\0'))
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_error_check(const char	*str)
{
	int		i;
	long	res;
	int		minus;

	i = 0;
	res = 0;
	minus = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i ++;
	if (str[i] == '-')
		minus = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = ft_checker_helper(str, res, i, minus);
	if (res == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	exec_exit(char **com, t_env **env)
{
	char		*trimed_com;
	extern int	g_status;

	(void)env;
	if (com[1] == NULL)
		exit(g_status);
	if (com[2] != NULL)
		exit(EXIT_FAILURE);
	trimed_com = ft_strtrim(com[1], " ");
	if (ft_error_check(trimed_com) == FAILURE)
		exit(255);
	exit(ft_atoi(trimed_com));
	free(trimed_com);
	return (SUCCESS);
}
