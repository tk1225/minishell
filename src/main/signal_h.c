/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:24:26 by atito             #+#    #+#             */
/*   Updated: 2023/03/09 21:51:54 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	signal_heredoc(int sig)
{
	g_status = 128 + sig;
	close(STDIN_FILENO);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
