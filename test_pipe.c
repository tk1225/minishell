# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <err.h>

int main(int artc, char*argv[]){
	int fd[2];

	if (pipe(fd) == -1)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;

	if (pid1 == 0)
	{
		//child
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return 3;

	if (pid2 == 0)
	{
		//child
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "icmp_seq=1", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}