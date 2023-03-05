/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:24:26 by atito             #+#    #+#             */
/*   Updated: 2023/03/05 19:25:15 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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
