#ifndef EXEC_H
# define EXEC_H

int		exec_set(char **com);

int		exec_pwd(void);
int		exec_echo(char **com);
int		exec_env(void);
int		exec_export(char **com);

#endif
