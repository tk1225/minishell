/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:32:12 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 14:32:26 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

t_env	*env_struct(char **envp)
{
	size_t	cnt;
	t_env	*out;
	t_env	*tmp;

	cnt = 0;
	tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
	out = tmp;
	tmp->prev = NULL;
	tmp->key = ft_substr(envp[cnt], 0, ft_strlen(envp[cnt]) - \
	ft_strlen(ft_strchr(envp[cnt], '=')));
	tmp->value = ft_substr(envp[cnt], ft_strlen(tmp->key) + 1, \
	ft_strlen(envp[cnt]) - ft_strlen(tmp->key) - 1);
	cnt += 1;
	while (envp[cnt])
	{
		tmp->next = (t_env *)alloc_exit(sizeof(t_env), 1);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->key = ft_substr(envp[cnt], 0, ft_strlen(envp[cnt]) - \
		ft_strlen(ft_strchr(envp[cnt], '=')));
		tmp->value = ft_substr(envp[cnt], ft_strlen(tmp->key) + 1, \
		ft_strlen(envp[cnt]) - ft_strlen(tmp->key) - 1);
		cnt += 1;
	}
	tmp->next = NULL;
	return (out);
}

void	check_heredoc(char **res)
{
	size_t	cnt;
	char	*delimiter;

	cnt = 0;
	while (res[cnt])
	{
		if (ft_strncmp(res[cnt], "<<", 3) == 0)
		{
			delimiter = res[cnt + 1];
			if (delimiter == NULL)
				exit(2);
			read_heredoc(delimiter);
		}
		cnt += 1;
	}
}

void	exec_line(char *line, t_env	*env)
{
	char	**res;
	t_tree	**tree;

	if (ft_strlen(line) == 0 && g_status == 130)
		g_status = 1;
	if (ft_strlen(line) > 0)
	{
		add_history(line);
		res = lexer(line);
		check_heredoc(res);
		tree = parser(res);
		if (syntax_check(*tree) > 0 && !((*tree)->com && !(*tree)->com[0]))
		{
			perror("syntax error");
			g_status = 2;
		}
		else
			g_status = exec_recursion(*tree, &env);
		free_tree(*tree);
		free(tree);
		free(res);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = env_struct(envp);
	// unset OLDPWD
	while (1)
	{
		rl_outstream = stderr;
		set_signal_read();
		line = readline("> ");
		if (line == NULL)
			break ;
		exec_line(line, env);
		free(line);
	}
	free_env(env);
	exit(g_status);
	return (0);
}
