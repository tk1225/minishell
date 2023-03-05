/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:06:51 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 12:53:44 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	handle_signals(int sig)
{
	g_status = 128 + sig;
}

static void	reset_prompt(int sig)
{
	g_status = 128 + sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_heredoc(int sig)
{
	g_status = 128 + sig;
	close(STDIN_FILENO);
}
