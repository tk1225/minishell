#include "minishell.h"

extern int	g_status;

void	handle_signals(int sig)
{
	if (sig == SIGINT)
		g_status = 130;
	if (sig == SIGQUIT)
		g_status = 131;
}

int	signal_check(void)
{
	if (g_status == 130 || g_status == 131)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
