#include "minishell.h"

int	ft_overflow_checker(const char *str, long res, int i, int minus)
{
	if (minus == 0)
	{
		if (((res > LONG_MAX / 10) && (str[i + 1] != '\0')) || \
		((res == LONG_MAX / 10) && (str[i + 1] >= '8')))
			return (1);
	}
	else
	{
		if (((res > LONG_MAX / 10) && (str[i + 1] != '\0')) || \
		((res == LONG_MAX / 10) && (str[i + 1] >= '9')))
			return (-1);
	}
	return (0);
}

static	int	ft_checker_helper(const char *str, long res, int i, int minus)
{
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (FAILURE);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res + str[i] - '0';
		if (ft_overflow_checker(str, res, i, minus) == 1)
			return (FAILURE);
		else if (ft_overflow_checker(str, res, i, minus) == -1)
			return (FAILURE);
		res *= 10;
		i++;
	}
	if (!(str[i] == '\0'))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_error_check(const char	*str)
{
	int		i;
	long	res;
	int		minus;

	i = 0;
	res = 0;
	minus = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i ++;
	if (str[i] == '-')
		minus = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = ft_checker_helper(str, res, i, minus);
	if (res == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	exec_exit(char **com)
{
    //FAILURE check必要
    if (com[2] != NULL)
        exit(1);
    if (ft_error_check(com[1]) == FAILURE)
        exit(255);
    exit(ft_atoi(com[1]));
 
	return (SUCCESS);
}