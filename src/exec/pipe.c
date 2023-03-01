#include "minishell.h"

int handle_pipe(t_tree *tree, t_env **envp)
{
    int pfd[2][2];
    pid_t pid1, pid3;
    // pid_t pid1, pid2, pid3;

    if (pipe(pfd[0]) == -1 || pipe(pfd[1]) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    //最初のみ
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) { // child process 3
        dup2(pfd[1][0], STDIN_FILENO);
        close(pfd[0][0]);
        close(pfd[0][1]);
        close(pfd[1][0]);
        close(pfd[1][1]);
		executer(tree->right->com, envp);
        exit(EXIT_FAILURE);
    }

    //pipeの右側(最後以外の中間)
    int i = 0;
    char **com;
    t_tree *p_tree;
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
            dup2(pfd[i][0], STDIN_FILENO);
            dup2(pfd[i + 1][1], STDOUT_FILENO);
            close(pfd[i][0]);
            close(pfd[i][1]);
            close(pfd[i + 1][0]);
            close(pfd[i + 1][1]);
            executer(com, envp);
            exit(EXIT_FAILURE);
        }
        p_tree = tree->left;
        i++;
        if (p_tree->left->stat == COM)
            break;
    }
    //pipeの左側がコマンドの場合(最初)
    pid3 = fork();

    if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) { // child process 1
        dup2(pfd[0][1], STDOUT_FILENO);
        close(pfd[0][0]);
        close(pfd[0][1]);
        close(pfd[1][0]);
        close(pfd[1][1]);
		executer(tree->left->left->com, envp);
        exit(EXIT_FAILURE);
    }

    close(pfd[0][0]);
    close(pfd[0][1]);
    close(pfd[1][0]);
    close(pfd[1][1]);

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