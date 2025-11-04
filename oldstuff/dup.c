//short test for dup dup2 and pipe
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h> //EXIT_FAILURE EXIT_SUCCESS

enum e_fds
{
	IN = 0,
	OUT,
	COUNT,
};

int main() {
    int		std[COUNT];
    pid_t	pid;
    char	buffer[100];
    
	if (pipe(std) == -1)
        return (EXIT_FAILURE);
    pid = fork();
    if (pid < 0)
        return (EXIT_FAILURE);
    if (pid == 0)
	{
        close(std[IN]);
        dup2(std[OUT], STDOUT_FILENO);
		int n = read(STDIN_FILENO, buffer, 99);
		if (n > 0)
		{
			buffer[n] = 0;
			puts(buffer);
		}
        close(std[OUT]);
    }
	else
	{
        close(std[OUT]);
        int n = read(std[IN], buffer, sizeof(buffer) - 1);
        if (n > 0)
		{
            buffer[n] = '\0';
            printf("Parent received: %s", buffer);
        }
        close(std[IN]);
		wait(NULL);
    }
    return (EXIT_SUCCESS);
}

/* psuedo function for simple-argv-shell.c
#include <stdio.h>
extern char **environ;
int exec(int argc, char **argv, int *curr)
{
	static int prev[2];
	static int next[2];
	static int ret;

	if (argv[*curr + 1][0] == '|')
		pipe(next);
	
	pid_t id = fork();
	if (id == 0)
	{
		if (*curr > 1 && argv[*curr - 1][0] == '|' && argv[*curr - 1][1] != '|'
			&& dup2(prev[0], STDIN_FILENO) != -1
			&& !close(prev[0]) && !close(prev[1]))
			return (EXIT_FAILURE);
		if (*curr + 1 < argc && argv[*curr + 1][0] == '|' && argv[*curr + 1][1] != '|'
			&& dup2(next[1], STDOUT_FILENO) != -1
			&& !close(next[0]) && !close(next[1]))
			return (EXIT_FAILURE);
		ret = execve(argv[*curr], NULL, environ);
	}
	else
	{
		if (*curr > 0 && argv[*curr - 1][0] == '|'
			&& !close(prev[0]) && !close(prev[1]))
			return (EXIT_FAILURE);
		prev[0] = next[0];
		prev[1] = next[1];
		//next[0] = 0;
		//next[1] = 1;
	}
	return (EXIT_SUCCESS);
}
*/
