/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:06:51 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 11:04:17 by takumasaoka      ###   ########.fr       */
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

void	set_signal_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, handle_heredoc);
}

void	set_signal_run(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}

void	set_signal_read(void)
{
	signal(SIGINT, reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}
