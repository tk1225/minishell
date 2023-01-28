/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takumasaokamoto <takumasaokamoto@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:30:46 by takumasaoka       #+#    #+#             */
/*   Updated: 2023/01/28 17:53:54 by takumasaoka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int executer(int argc, char **parsed_line, char **envp)
{
  char    *command_path = "/bin/echo";

  (void)argc;
  // (void)argv;
  // (void)envp;
  // if (argc == 2) {
    /* 実行時引数（パス名）をexecveの引数にする */
    // exargv[2] = argv[1];
    if (execve(command_path, parsed_line, envp) == -1)
    {
      // printf("%sコマンドが実行できませんでした\n", command_path);
      // perror(' ');
      // return_code = 1;
    }
  // }
  // else
  // {
  //   printf('実行時引数の数が不当です\n');
  //   return_code = 2;
  // }
  return 0;
  // return return_code;
}
