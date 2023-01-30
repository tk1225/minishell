/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:30:46 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/30 18:57:22 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int executer(int argc, char **parsed_line, char **envp)
{
  char    *command_path;
  pid_t       pid;

  command_path = ft_strjoin("/bin/", parsed_line[0]);
  (void)argc;
  pid = fork();
  int         status;
  
  if (-1 == pid)
    err (EXIT_FAILURE, "can not fork");
  else if (0 == pid)
  {   
    //子プロセス
    if (execve(command_path, parsed_line, envp) == -1){}
        exit(EXIT_SUCCESS);
  }
  else
  {
    //親プロセス
    wait(&status);
    //ゾンビプロセス回避
    waitpid(pid, &status, 0);
  }
  return 0;
}
