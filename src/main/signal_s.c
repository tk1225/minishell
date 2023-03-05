/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:17:59 by atito             #+#    #+#             */
/*   Updated: 2023/03/05 19:26:08 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	handle_signals(int sig)
{
	g_status = 128 + sig;
}

void	set_signal_run(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
