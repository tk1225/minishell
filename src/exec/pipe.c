#include "minishell.h"

int count_pipe(t_tree *tree)
{
    if (tree->stat == PIPE)
        return (1 + count_pipe(tree->left) + count_pipe(tree->right));
    else
        return (0);
}

void close_pipe(int pipe_count, int pipefd[4096][2])
{
    int tmp;

    tmp = 0;
    while (tmp < pipe_count)
    {
        close(pipefd[tmp][0]);
        close(pipefd[tmp][1]);
        tmp ++;
    }
}

int handle_pipe(t_tree *tree, t_env **envp)
{
    int pipefd[4096][2];
    pid_t pid3;
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
    int i = pipe_count;
    char **com;
    t_tree *p_tree;
    p_tree = tree;
    while (p_tree->stat != COM)
    {
        com = p_tree->right->com;
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            dup2(pipefd[i - 1][READ], STDIN_FILENO);
            if (pipe_count != i)
                dup2(pipefd[i][WRITE], STDOUT_FILENO);
            close_pipe(pipe_count, pipefd);
            executer(com, envp);
            exit(EXIT_FAILURE);
        }
        p_tree = p_tree->left;
        i--;
    }
    com = p_tree->com;
    //pipeの左側がコマンドの場合(最初)
    pid3 = fork();
    if (pid3 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid3 == 0) { // child process 1
        dup2(pipefd[0][WRITE], STDOUT_FILENO);
        close_pipe(pipe_count, pipefd);
		executer(com, envp);
        exit(EXIT_FAILURE);
    }
    close_pipe(pipe_count, pipefd);
    return 0;
}
