#include "minishell.h"

int g_status_code = 0;

int	read_heredoc(const char *delimiter)
{
	char	*line;
	int fd = open(".tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);

	while (1)
	{
		if (g_status_code == 130)
			break;
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0 || g_status_code == 130)
		{
			if (g_status_code == 130)
				g_status_code = 1;
			free(line);
			break ;
		}
		//次の行からがHEREDOCの内容
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (1);
}

t_env	*env_struct(char **envp)
{
	size_t	cnt;
	t_env	*out;
	t_env	*tmp;

	cnt = 0;
	tmp = (t_env *)alloc_exit(sizeof(t_env), 1);
	out = tmp;
	tmp->prev = NULL;
	tmp->key = ft_substr(envp[cnt], 0, ft_strlen(envp[cnt]) - ft_strlen(ft_strchr(envp[cnt], '=')));
	tmp->value = ft_substr(envp[cnt], ft_strlen(tmp->key) + 1, ft_strlen(envp[cnt]) - ft_strlen(tmp->key) - 1);
	cnt += 1;
	while (envp[cnt])
	{
		tmp->next = (t_env *)alloc_exit(sizeof(t_env), 1);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->key = ft_substr(envp[cnt], 0, ft_strlen(envp[cnt]) - ft_strlen(ft_strchr(envp[cnt], '=')));
		tmp->value = ft_substr(envp[cnt], ft_strlen(tmp->key) + 1, ft_strlen(envp[cnt]) - ft_strlen(tmp->key) - 1);
		cnt += 1;
	}
	tmp->next = NULL;
	return (out);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	int status;
	char *line = NULL;
	t_tree **tree;
	t_env *env;

	env = env_struct(envp);
	while (1)
	{
		// test用
		rl_outstream = stderr;
		// testの際に外す
		rl_event_hook = signal_check;
    	signal(SIGINT, handle_signals); 
    	signal(SIGQUIT, SIG_IGN); 
		line = readline("> ");
		if (line == NULL)
			break;
		if (ft_strlen(line) == 0 && g_status_code == 130)
			g_status_code = 1;
		if (ft_strlen(line) > 0)
		{
			char **res;
			add_history(line);
			res = lexer(line);
			size_t	cnt;
			char *delimiter;
			cnt = 0;
			while (res[cnt])
			{
				// printf("res%s\n",res[cnt]);
				if (ft_strncmp(res[cnt], "<<", 2) == 0)
				{
					delimiter = res[cnt + 1];
					if (delimiter == NULL)
						exit(2);
					read_heredoc(delimiter);
				}
				cnt += 1;
			}
			tree = parser(res);
			if (syntax_check(*tree) > 0)
			{
				perror("syntax error");
				g_status_code = 2;
				continue;
			}
			else
			{
				status = exec_recursion(*tree, &env);
			}
			if (g_status_code == 130)
			{
				write(1, "\n", 1);
			}
			
			// printf("%d", WEXITSTATUS(status));
			// write(1,ft_itoa(WEXITSTATUS(status)), 4);
			// write(1,ft_itoa(g_status_code), 4);
			// if (g_status_code != 130)
			g_status_code = WEXITSTATUS(status);
			free(line);
		}
	}
	exit(g_status_code);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks minishell");
// }
