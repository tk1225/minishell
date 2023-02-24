#include "minishell.h"

extern int status_code;

void    handle_signals(int sig)
{
    if (sig == SIGINT)
    {
        status_code = 130;
    }
}

int    signal_check(void)
{
    if (status_code == 130)
    {
		// write(1, "status is 130", 13);
        rl_replace_line("", 0); 
        rl_done = 1;
    }
    return (0);
}

// int    signal_heredoc_check(void)
// {
//     if (status_code == 130)
//     {
//         rl_on_new_line();
// 		rl_replace_line("", 0);
// 		// rl_on_new_line();
// 		ft_putstr_fd("\n", 1);
// 		rl_redisplay();
//         // rl_done = 1;
//     }
//     return (0);
// }