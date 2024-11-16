#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <sys/wait.h>
#include <readline/history.h>
#include "minishell.h"

#define EXITFAILURE 1
#define EXITSUCCESS 0

const char	*builtins[BI_TOTAL] = {
	[BI_ECHO] = "echo",
	[BI_CD] = "cd",
	[BI_PWD] = "pwd",
	[BI_EXPORT] = "export",
	[BI_UNSET] = "unset",
	[BI_ENV] = "env",
	[BI_EXIT] = "exit",
};

const char	**path;

#include "getline.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//reads whole lines and merges previous lines until the quote character or EOF.
// TODO: performance boost: control the buffer to read on top of input_start.
static ssize_t	ms_read_lines_until_quote(char **input, size_t *n, 
										  size_t *i, int quotechar)
{
	char	*secquote;
	ssize_t	ret;

	return (0);
	(*i)++;
	secquote = strchr(*input + *i, quotechar);
	while (secquote == NULL)
	{
		if (write (STDOUT_FILENO, "> ", 2) < 0)
			return (-1);
		ret = ft_readline(input, n, STDIN_FILENO);
		if (ret < 0)
			return (ret);
		secquote = strchr(*input + *i, quotechar);
		if (secquote == NULL)
			*i += ret;
	}
	*i += secquote - (*input + *i);
	return (0);
}

//returns one or more lines or NULL on malloc(3)/read(2) error.
ssize_t	ms_checkstring(char **input, size_t *n)
{	
	ssize_t			ret;
	size_t			i;

	i = 0;
	while ((*input)[i] != '\0')
	{
		if (strchr("\"\'", (*input)[i]) != NULL)
		{
			ret = ms_read_lines_until_quote(input, n, &i, (*input)[i]);
			if (ret < 0)
				return (-1);
		}
		i++;
	}
	return ret;
}

//perror("couldn't write() to stdout")
//perror("couldn't malloc() in ft_getline()")
//perror("couldn't malloc() in tokenise()")

    //signal(SIGQUIT, ms_exit);
    //signal(SIGINT, ms_exit);
	
int	main(int argc, char *argv[], char *envp[])
{
	t_input		input;
	ssize_t		ret;
	
	while (1)
	{
		if (write(STDOUT_FILENO, "minishell$ ", 11) != 11)
			return (EXITFAILURE);
		ret = ft_readline(&input.str, &input.bufsize, STDIN_FILENO);
		//if (ret > 0)
		//	ret = ms_checkquotes(&input.str, &input.bufsize, STDIN_FILENO)
		if (ret < 0)
			return (EXITFAILURE);
		if (ret == 0)
			return (free(input.str), EXITSUCCESS);
		add_history(input.str);
		if (ms_tokenise(&input) == false)
			return (free(input.str), EXITFAILURE);
		if (ms_expand_envs(&input) == false)
			return (EXITFAILURE);
		if (ms_create_ast(&input) == false)
			return (free(input.str), EXITFAILURE);
		if (ms_exec(&input, argc, argv, envp) == false)
			return (free(input.str), EXITFAILURE);
	}
	free(input.str);
	return (EXITSUCCESS);
}

