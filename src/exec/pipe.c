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

void init_pipe(int pipe_count, int pipefd[4096][2])
{
    int j;

    j = 0;
    while (j < pipe_count)
    {
        pipe(pipefd[j]);
        //pipeerror
        j ++;
    }
}

static pid_t fork_process()
{
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return (pid);
}

static void cat_pipe(int pipe_count, int pipefd[4096][2], int i)
{
    if (i >= 1)
        dup2(pipefd[i - 1][READ], STDIN_FILENO);
    if (pipe_count != i)
        dup2(pipefd[i][WRITE], STDOUT_FILENO);
    close_pipe(pipe_count, pipefd);
}


int handle_pipe(t_tree *tree, t_env **envp, int pipe_count)
{
    int pipefd[4096][2];
    int i;
    char **com;
    t_tree *p_tree;

    i = pipe_count;
    init_pipe(pipe_count, pipefd);
    p_tree = tree;
    while (p_tree)
    {
        if (p_tree->stat == COM)
            com = p_tree->com;
        else
            com = p_tree->right->com;
        if (fork_process() == 0)
        {
            cat_pipe(pipe_count, pipefd, i);
            // if (i >= 1)
            //     dup2(pipefd[i - 1][READ], STDIN_FILENO);
            // if (pipe_count != i)
            //     dup2(pipefd[i][WRITE], STDOUT_FILENO);
            // close_pipe(pipe_count, pipefd);
            executer(com, envp);
        }
        p_tree = p_tree->left;
        i--;
    }
    close_pipe(pipe_count, pipefd);
    return 0;
}
