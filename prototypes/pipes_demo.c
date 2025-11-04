//minimal example how a pipeline between 2
//processes (in this case 2 commands: ls and cat) can be made.
//EXAMPLE1 = fork() example.
//EXAMPLE2 = fork() + pipe() example.
//EXAMPLE3 = fork() + pipe() + execve(ls, cat) example.

#include <unistd.h> //write(), pid_t, pipe(), fork(), close(),
#include <sys/wait.h> //wait()

#define EXAMPLE1
int main(void)
{
#ifdef EXAMPLE1
	pid_t	pid = fork();

	if (pid < 0)
		write(1, "fork() somehow failed\n", 22);
	else if (pid == 0)
		write(1, "called from parent\n", 19);
	else
		write(1, "called from child\n", 18);
#endif //EXAMPLE1
#ifdef EXAMPLE2
	//TODO: pipe() example
#endif //EXAMPLE2
#ifdef EXAMPLE3
	char	*cmd1 = "/usr/bin/ls";
	char	*cmd2 = "/usr/bin/cat";
	int		fd[2];
	pid_t	first;
	pid_t	second;

	if (pipe(fd) == -1) return (1);

	first = fork();
	if (first < 0) return (1);
	else if (first == 0)
	{
		write(1, "[entered first]\n", 16);
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (write(2, "Error: dup2() in first\n", 23), 1);
		close(fd[1]);
		char *args[] = {cmd1, NULL};
		write(1, "[leaving first]\n", 16);
		if (execve(args[0], args, NULL) < 0)
			return (write(2, "Error: execve() in first\n", 25), 1);
	}

	second = fork();
	if (second < 0) return (1);
	else if (second == 0)
	{
		write(1, "[entered second]\n", 17);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (write(2, "Error: dup2() in second\n", 23), 1);
		close(fd[0]);
		char *args[] = {cmd2, NULL};
		write(1, "[leaving second]\n", 17);
		if (execve(args[0], args, NULL) < 0)
			return (write(2, "Error: execve() in second\n", 25), 1);
	}

	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
#endif //EXAMPLE3
	return (0);
}
