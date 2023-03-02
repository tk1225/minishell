#include "minishell.h"

int	ch_dir(char *path)
{
	int	flag;

	flag = chdir(path);
	free(path);
	return (flag);
}
