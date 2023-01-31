#include "minishell.h"

char **parser(char *line)
{
	char	**res;

	res = lexer(line);
	int i = 0;
	while (1)
	{
		if (!res[i])
			break ;
		printf("%s\n", res[i++]);
	}
	return (res);
}
