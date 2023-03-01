#include "minishell.h"

// int	handle_pipe(t_tree *tree, t_env **envp)
// {
// 	int	pipefd[2];
// 	int	pid;
// 	// int	status;

// 	if (pipe(pipefd) == -1)
// 		return (1);
// 	pid = fork();
// 	if (pid < 0)
// 		return (2);
// 	if (pid == 0)
// 	{
// 		close(pipefd[READ]);
// 		dup2(pipefd[WRITE], STDOUT_FILENO);
// 		close(pipefd[WRITE]);
// 		if (tree->left->stat == COM)
// 			executer(tree->left->com, envp);
// 		// else if (tree->left->stat == PIPE)
// 		// 	handle_pipe(tree->left, envp);
// 	}
// 	int	pid2;
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		return (2);
// 	if (pid2 == 0)
// 	{
// 		close(pipefd[WRITE]);
// 		dup2(pipefd[READ], STDIN_FILENO);
// 		close(pipefd[READ]);
// 	// wait(&status);
// 	// waitpid();
// 		executer(tree->right->com, envp);
// 	}
// 	return (0);
// }

int handle_pipe(t_tree *tree, t_env **envp)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        /* First child process executes "ls" command */
        close(pipefd[0]); /* Close unused read end of the pipe */
        dup2(pipefd[1], STDOUT_FILENO); /* Redirect stdout to the write end of the pipe */
        if (tree->left->stat == COM)
			executer(tree->left->com, envp);
        // execlp("ls", "ls", NULL);
        perror("exec ls");
        exit(EXIT_FAILURE);
    }
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        /* Second child process executes "grep" command */
        close(pipefd[1]); /* Close unused write end of the pipe */
        dup2(pipefd[0], STDIN_FILENO); /* Redirect stdin to the read end of the pipe */
        executer(tree->right->com, envp);
        perror("exec grep");
        exit(EXIT_FAILURE);
    }
        /* Parent process */
        close(pipefd[0]); /* Close unused read end of the pipe */
        close(pipefd[1]); /* Close unused write end of the pipe */
        waitpid(pid1, NULL, 0); /* Wait for the first child process to exit */
        waitpid(pid2, NULL, 0); /* Wait for the second child process to exit */
    // }

    return 0;
}
