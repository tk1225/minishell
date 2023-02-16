#ifndef EXEC_H
# define EXEC_H

int	exec_set(char **com, char **envp);

int	exec_cd(char **com, char **envp);
int	exec_echo(char **com, char **envp);
int	exec_env(char **com, char **envp);
int	exec_exit(char **com, char **envp);
int	exec_export(char **com, char **envp);
int	exec_pwd(char **com, char **envp);
int	exec_unset(char **com, char **envp);

#endif
