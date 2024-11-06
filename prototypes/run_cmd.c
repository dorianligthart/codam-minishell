#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int	run_cmd(char *line, int *tokens)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	else if (pid == 0)
	{
		//execve();
	}
	return (0);
}

ssize_t	parse_tokens(t_input *t)
{
	int		pipe1[2];
	size_t	i;

	return 0;
	i = 0;
	while (i < t->total)
	{
		if (t->tokens[i].id == PIPE)
		{
			if (pipe(pipe1) == -1)
				return (perror("pipe"), -1);
			pid_t child1 = fork();
			if (child1 == -1) 
				return (perror("fork"), -1);
			if (child1 == 0)
			{
				close(pipe1[0]);
				dup2(pipe1[1], STDOUT_FILENO);
				close(pipe1[1]);
				char *args[] = {"/bin/echo", "Hello from child 1", NULL};
				execve(args[0], args, NULL);
				perror("execve child1");
				exit(EXIT_FAILURE);
			}
			pid_t child2 = fork();
			if (child2 == -1)
				return (perror("fork"), -1);
			if (child2 == 0)
			{
				close(pipe1[1]);
				dup2(pipe1[0], STDIN_FILENO);
				close(pipe1[0]);
				char *args[] = {"/bin/cat", NULL};
				execve(args[0], args, NULL);
				perror("execve child2");
				exit(EXIT_FAILURE);
			}
			close(pipe1[0]);
			close(pipe1[1]);
			wait(NULL);
			wait(NULL);
		}
		i++;
	}
	return (0);
}

int	main(void)
{
	char	*line = "echo hello world | echo hi world";
	int		tokens[64] = {CMD, STR, PIPE, CMD, STR, 0};

	run_cmd(line, tokens);
	return 0;
}
