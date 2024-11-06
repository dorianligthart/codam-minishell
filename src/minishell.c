#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <sys/wait.h>
#include "minishell.h"

// checks if cmd is a builtin or whether it exists or not using access()
int		check_cmd(void)
{
	return (0);
}


ssize_t	get_cmd(t_input *t)
{
	(void)t;
	return (0);
}

void	ms_exit(int exitcode)
{
	//printf("\nexiting...\n");
	exit(exitcode);
}

//perror("couldn't write() to stdout")
//perror("couldn't malloc() in ft_getline()")
//perror("couldn't malloc() in tokenise()")
//signal(SIGINT, exit);//put this in quotesread()
int	main(void)
{
	//t_input	*input;
	char			*input;

    signal(SIGQUIT, ms_exit);
    signal(SIGINT, ms_exit);
	while (1)
	{
		if (write(STDOUT_FILENO, "minishell$ ", 11) != 11)
			return (1);
		input = ms_read_stdin();
		if (input == NULL)
			return (1);
		//t = ms_get_tokens(input);
		//if (t == NULL || t->tokens == NULL)
		//	return (1);
		//if (parse_tokens(t) < 0)
		//	return (1);
		free(input);
	}
	return (0);
}

