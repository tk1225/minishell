#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
		// rl_replace_line("$ ", 0);
		// rl_redisplay();
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// EOF
	}
}

int	set_signal()
{
	// ◦ ctrl-C displays a new prompt on a new line.
	// ◦ ctrl-D exits the shell.
	// ◦ ctrl-\ does nothing.
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}