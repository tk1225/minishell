#include "minishell.h"

int count_pipe(t_tree *tree)
{
    if (tree->stat == PIPE)
        return (1 + count_pipe(tree->left) + count_pipe(tree->right));
    else
        return (0);
}

int handle_pipe(t_tree *tree, t_env **envp)
{
    int pipefd[4096][2];
    pid_t pid1, pid3;
    int pipe_count;

    pipe_count = count_pipe(tree);
    if (pipe_count == 0)
        return (1);

    int j;
    j = 0;
    while (j < pipe_count)
    {
        pipe(pipefd[j]);
        //pipeerror
        j ++;
    }
    // if (pipe(pipefd[0]) == -1 || pipe(pipefd[1]) == -1) {
    //     perror("pipe");
    //     exit(EXIT_FAILURE);
    // }
    //最初のみ最後のコマンド
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) { // child process 3
        dup2(pipefd[pipe_count - 1][READ], STDIN_FILENO);
        // close(pipefd[0][0]);
        // close(pipefd[0][1]);
        close(pipefd[pipe_count - 1][0]);
        close(pipefd[pipe_count - 1][1]);
		executer(tree->right->com, envp);
        exit(EXIT_FAILURE);
    }

    //pipeの右側(最後以外の中間)
    int i = pipe_count - 1;
    // int i = 0;
    char **com;
    t_tree *p_tree;

    if (tree->left->stat != COM)
    {
        p_tree = tree->left;
        com = tree->left->right->com;

        while (1)
        {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid == 0)
            {
                dup2(pipefd[i - 1][READ], STDIN_FILENO);
                dup2(pipefd[i][WRITE], STDOUT_FILENO);
                close(pipefd[i - 1][0]);
                close(pipefd[i - 1][1]);
                close(pipefd[i][0]);
                close(pipefd[i][1]);
                executer(com, envp);
                exit(EXIT_FAILURE);
            }
            p_tree = tree->left;
            i--;
            if (p_tree->left->stat == COM)
                break;
        }
    }
    //pipeの左側がコマンドの場合(最初)
    pid3 = fork();

    if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) { // child process 1
        dup2(pipefd[0][WRITE], STDOUT_FILENO);
        close(pipefd[0][0]);
        close(pipefd[0][1]);
        close(pipefd[1][0]);
        close(pipefd[1][1]);
		executer(com, envp);
		// executer(tree->left->left->com, envp);
        exit(EXIT_FAILURE);
    }

    int tmp;
    tmp = 0;
    while (tmp < pipe_count)
    {
        close(pipefd[tmp][0]);
        close(pipefd[tmp][1]);
        tmp ++;
    }
    // close(pipefd[0][0]);
    // close(pipefd[0][1]);
    // close(pipefd[1][0]);
    // close(pipefd[1][1]);
    // free(pipefd);
    // waitpid(pid1, &status, 0);
    // waitpid(pid2, &status, 0);
    // waitpid(pid3, &status, 0);

    return 0;
}


// pid2 = fork();

    // if (pid2 == -1) {
    //     perror("fork");
    //     exit(EXIT_FAILURE);
    // }

    // if (pid2 == 0) { // child process 2
    //     dup2(pfd[0][0], STDIN_FILENO);
    //     dup2(pfd[1][1], STDOUT_FILENO);
    //     close(pfd[0][0]);
    //     close(pfd[0][1]);
    //     close(pfd[1][0]);
    //     close(pfd[1][1]);
	// 	executer(tree->left->right->com, envp);
    //     exit(EXIT_FAILURE);
    // }

// int handle_pipe(t_tree *tree, t_env **envp)
// {
//     int pipefd[2][2];
//     pid_t pid1, pid2, pid3;

//     if (pipe(pipefd[0][0]) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid1 = fork();
//     if (pid1 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid1 == 0) {
//         /* First child process executes "ls" command */
//         close(pipefd[0][0]); /* Close unused read end of the pipe */
//         dup2(pipefd[0][1], STDOUT_FILENO); /* Redirect stdout to the write end of the pipe */
//         // if (tree->left->stat == COM)
// 		executer(tree->right->com, envp);
//         // execlp("ls", "ls", NULL);
//         perror("exec ls");
//         exit(EXIT_FAILURE);
//     }
//     pid2 = fork();
//     if (pid2 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid2 == 0) {
//         /* Second child process executes "grep" command */
//         close(pipefd[0][1]); /* Close unused write end of the pipe */
//         dup2(pipefd[0][0], STDIN_FILENO); /* Redirect stdin to the read end of the pipe */
//         executer(tree->right->com, envp);
//         perror("exec grep");
//         exit(EXIT_FAILURE);
//     }

//     pid3 = fork();
//     if (pid3 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid3 == 0) {
//         /* First child process executes "ls" command */
//         close(pipefd[0][0]); /* Close unused read end of the pipe */
//         dup2(pipefd[0][1], STDOUT_FILENO); /* Redirect stdout to the write end of the pipe */
//         // if (tree->left->stat == COM)
// 		executer(tree->left->left->com, envp);
//         // execlp("ls", "ls", NULL);
//         perror("exec ls");
//         exit(EXIT_FAILURE);
//     }
//         /* Parent process */
//         close(pipefd[0][0]); /* Close unused read end of the pipe */
//         close(pipefd[0][1]); /* Close unused write end of the pipe */
//         close(pipefd[1][0]); /* Close unused write end of the pipe */
//         close(pipefd[1][1]); /* Close unused write end of the pipe */
//         // waitpid(pid1, NULL, 0); /* Wait for the first child process to exit */
//         // waitpid(pid2, NULL, 0); /* Wait for the second child process to exit */
//     // }

//     return 0;
// }