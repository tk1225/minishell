/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:06:51 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/03/05 19:26:22 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	reset_prompt(int sig)
{
	g_status = 128 + sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_read(void)
{
	signal(SIGINT, reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}
