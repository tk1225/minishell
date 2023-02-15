#include "minishell.h"

int	exec_exit(char **com)
{
    //error check必要
    exit(ft_atoi(com[1]));
 
	return (SUCCESS);
}