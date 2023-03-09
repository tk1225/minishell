/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:17:59 by atito             #+#    #+#             */
/*   Updated: 2023/03/09 21:18:56 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	handle_signals(int sig)
{
	g_status = 128 + sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	set_signal_run(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
