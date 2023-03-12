/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:19:39 by atito             #+#    #+#             */
/*   Updated: 2023/03/12 16:01:08 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_arr(char **arr, t_env **env)
{
	size_t	cnt;
	t_env	*top;

	cnt = 0;
	while (arr[cnt])
	{
		top = *env;
		while (top)
		{
			if (ft_strncmp(arr[cnt], top->key, ft_strlen(arr[cnt]) + 1) == 0)
			{
				if (put_env(top) == -1)
					return (-1);
			}
			top = top->next;
		}
		cnt += 1;
	}
	free(arr);
	arr = NULL;
	return (0);
}

static int	sort_env(t_env **env)
{
	size_t	len;
	size_t	cnt;
	t_env	*top;
	char	**sort_arr;

	len = 0;
	top = *env;
	while (top)
	{
		len += 1;
		top = top->next;
	}
	sort_arr = (char **)alloc_exit(sizeof(char *), len + 1);
	top = *env;
	cnt = 0;
	while (cnt < len)
	{
		sort_arr[cnt++] = top->key;
		top = top->next;
	}
	sort_arr[cnt] = NULL;
	bubble_sort(sort_arr);
	if (put_arr(sort_arr, env) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	search_env(t_env **top, char *key, char *value, int flag)
{
	while (*top)
	{
		if (ft_strncmp((*top)->key, key, ft_strlen(key) + 1) == 0)
		{
			if (flag == 1)
				value = append_env(top, value);
			free(key);
			if (value)
			{
				free((*top)->value);
				(*top)->value = value;
			}
			else
				free(value);
			return (1);
		}
		if (!(*top)->next)
			break ;
		*top = (*top)->next;
	}
	return (0);
}

int	add_env(char *com, t_env **env)
{
	char	*key;
	char	*value;
	size_t	flag;
	t_env	*top;

	flag = 0;
	if (com[ft_strlen(com) - ft_strlen(ft_strchr(com, '=')) - 1] == '+')
		flag = 1;
	key = ft_substr(com, 0, ft_strlen(com) - \
		ft_strlen(ft_strchr(com, '=')) - flag);
	if (ft_atoi(key) != 0 || ft_strlen(key) == 0 || \
		key[ft_strlen(key) - 1] == '-' || key[ft_strlen(key) - 1] == '+')
		return (invalid_identifier(key));
	if (ft_strchr(com, '='))
		value = ft_substr(com, ft_strlen(key) + 1 + flag, \
			ft_strlen(com) - ft_strlen(key) - 1 - flag);
	else
		value = NULL;
	top = *env;
	if (search_env(env, key, value, flag) == 1)
	{
		*env = top;
		return (SUCCESS);
	}
	flag = add_back_env(env, key, value, top);
	return (flag);
}

int	exec_export(char **com, t_env **env)
{
	size_t	cnt;

	if (com[1] == NULL)
		return (sort_env(env));
	else
	{
		cnt = 1;
		while (com[cnt])
			add_env(com[cnt++], env);
		return (SUCCESS);
	}
	return (FAILURE);
}
