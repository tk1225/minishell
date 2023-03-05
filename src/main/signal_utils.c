/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 19:17:59 by atito             #+#    #+#             */
/*   Updated: 2023/03/05 19:18:26 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
