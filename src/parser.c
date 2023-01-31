#include "minishell.h"

char **parser(char *line)
{
	char	**res;

	res = lexer(line);
	for (int i = 0; i < 8; i++)
		printf("%s\n", res[i]);
	return (res);
}
