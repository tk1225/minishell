#include "minishell.h"

extern int g_status_code;

void	handle_signals(int sig)
{
	if (sig == SIGINT)
		g_status_code = 130;
}

int	signal_check(void)
{
	if (g_status_code == 130)
	{
		rl_replace_line("", 0); 
		rl_done = 1;
	}
	return (0);
}
