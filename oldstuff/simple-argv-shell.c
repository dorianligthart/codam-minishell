//Small simple shell program without ()
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int	my_cd(int argc, char **argv)
{
	if (argc > 1)
		return (puts("Error: my_cd() too many arguments\n"), EXIT_FAILURE);
	else if (chdir(argv[0]) == EXIT_FAILURE)
		return (perror("Error: my_cd()"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	my_pwd(int argc, char **argv)
{
	char	cwd[1024];

	if (getcwd(cwd, 1023) == NULL)
		return (perror("Error: my_pwd(): getcwd(3)"), EXIT_FAILURE);
	cwd[1023] = 0;
	if (write(STDOUT_FILENO, cwd, strlen(cwd)) != strlen(cwd)
			|| write(STDOUT_FILENO, "\n", 1) != 1)
		return (perror("Error: my_pwd(): write(2)"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	my_exit(int argc, char **argv)
{
	if (argc == 0)
		exit(0);
	if (argc == 1)
		exit(atoi(argv[1]));
	puts("Error: my_exit() too many arguments\n");
}

int	my_echo(int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < argc)
		if (puts(argv[i]) < 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	my_export(int argc, char **argv) //TODO: test
{
	char	*str;
	int		i;
	size_t	str_len;
	size_t	idlen;

	i = -1;
	while (++i < argc)
	{
		str_len = strlen(argv[i]);
		idlen = 0;
		while (str[idlen] && str[idlen] != '=')
			idlen++;
		str[idlen] = 0;
		if (idlen + 1 < str_len && setenv(str, str + idlen + 1, true) == EXIT_FAILURE)
			return (perror("Error: setenv() failed"), EXIT_FAILURE);
		else if (idlen + 1 == str_len && setenv(str, "", true) == EXIT_FAILURE)
			return (perror("Error: setenv() failed"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	my_unset(int argc, char **argv) //TODO: test
{
	int	i;

	i = -1;
	while (++i < argc)
		if (unsetenv(argv[i]) == EXIT_FAILURE) 
			return (perror("Error: unsetenv() failed"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

extern char **environ;

int	my_env(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc)
		return (puts("Error: my_env() too many arguments\n"), EXIT_FAILURE);
	else
		while (environ[++i])
			if (puts(environ[i]) < 0)
				return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

enum e_execmodes
{
	CONCURRENT = 0, // ;
	PIPE_PREV,      // | cmd ...    where `cmd` includes their args
	PIPE_NEXT,      // ... cmd |
	PIPE_BOTH,      // | cmd | 
	AND,            // ||
	OR,             // &&
};
	
//debug:
char	*modestrs[] = {
	"CONCURRENT", 
	"PIPE_PREV", 
	"PIPE_NEXT", 
	"PIPE_BOTH", 
	"AND", 
	"OR", 
};

int exec(int sub, char **argv, char *next_str, int mode)
{
	pid_t 		id;
	char	 	buffer[128];
	static int 	prev[2];
	static int 	next[2];
	static int	ret;

	if (mode == OR && ret == 0)
		return (EXIT_SUCCESS);
	if (mode == AND && ret != 0)
		return (EXIT_SUCCESS);
	if (next_str && next_str[0] == '|' && next_str[1] != '|')
	{
		if (mode == PIPE_PREV)
			mode =  PIPE_BOTH;
		else
			mode = PIPE_NEXT;
		if (pipe(next) == -1)
			return (EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
   	{
		//printf("---cmd: `%s`, args: %d mode: %s---\n", argv[0], sub, modestrs[mode]);
		if (mode == PIPE_PREV || mode == PIPE_BOTH)
			if (dup2(prev[0], STDIN_FILENO) == -1
			|| close(prev[0]) == -1
			|| close(prev[1]) == -1)
				return (EXIT_FAILURE);
		if (mode == PIPE_NEXT || mode == PIPE_BOTH)
			if (dup2(next[1], STDOUT_FILENO) != -1
			|| close(next[0]) == -1
			|| close(next[1]) == -1)
				return (EXIT_FAILURE);

		if (     !strcmp(argv[0], "echo") )
			ret = my_echo(sub - 1, argv + 1);
		else if (!strcmp(argv[0], "cd"))
			ret = my_cd(sub - 1, argv + 1);
		else if (!strcmp(argv[0], "pwd"))
			ret = my_pwd(sub - 1, argv + 1);
		else if (!strcmp(argv[0], "export"))
			ret = my_export(sub - 1, argv + 1);
		else if (!strcmp(argv[0], "unset"))
			ret = my_unset(sub - 1, argv + 1);
		else if (!strcmp(argv[0], "env"))
		ret = my_env(sub - 1, argv + 1);
		else if (!strcmp(argv[0], "exit"))
			ret = my_exit(sub - 1, argv + 1);
		else
		{
			memcpy(buffer, "/usr/bin/", 9); //TODO: make the example use $PATH??
			memset(buffer + 9, '\0', 128 - 9);
			if (argv[0][0] != '/'
			&& !(argv[0][0] == '.' && argv[0][1] == '/'))
				memcpy(buffer + strlen(buffer),
							argv[0], strlen(argv[0]));
			//printf("Executing '%s'\n", buffer);
			argv[sub] = NULL;
			execve(buffer, argv + 1, environ);
			return (perror("Error: execve()"), EXIT_FAILURE);
		}
	}
	else //in parent
	{
		if (((argv[-1][0] == '&' && argv[-1][1] == '&')
		  || (argv[-1][0] == '|' && argv[-1][1] == '|'))
				&& waitpid(id, &ret, 0) == -1)
			return (EXIT_FAILURE);
		if ((mode == PIPE_PREV || mode == PIPE_BOTH)
				&& close(prev[0] == -1) && close(prev[1]) == -1)
			return (EXIT_FAILURE);
		prev[0] = next[0];
		prev[1] = next[1];
	}
	return (EXIT_SUCCESS);
}

int	exec_all(int ac, char **av)
{
	int	i;
	int	sub;

	i = 0;
	while (i < ac)
	{
		sub = -1;
		while (++sub + i < ac) //skip to next ; | &
			if (av[i + sub][0] == ';' || av[i + sub][0] == '|' || av[i + sub][0] == '&')
				break ;
		//for (int b = 0; b < sub; b++) printf("got: %s, sub=%d\n", av[i + b], sub);

		if ((i + sub == 0 || i + sub == ac - 1) 
				&& av[i + sub][0] == '|' && av[i + sub][0] == '&')
			return (puts("Error: input can not begin or end on &&, ||, |\n"), EXIT_FAILURE);
		
		if ((i == 0 || (av[i + sub] && av[i + sub][0] == ';'))
				&& exec(sub, av + i, av[i + sub], CONCURRENT))
			return (EXIT_FAILURE);
		else if (av[i + sub] && av[i + sub][0] == '&' && av[i + sub][1] == '&'
				&& exec(sub, av + i, av[i + sub], AND))
			return (EXIT_FAILURE);
		else if (av[i + sub] && av[i + sub][0] == '|' && av[i + sub][1] == '|'
				&& exec(sub, av + i, av[i + sub], OR))
			return (EXIT_FAILURE);
		else if (av[i + sub] && av[i + sub][0] == '|'
				&& exec(sub, av + i, av[i + sub], PIPE_PREV))
			return (EXIT_FAILURE);
		i += sub;
	}
	return (EXIT_SUCCESS);
}
//OLD CODE ^^^ should be stable
//
//
//NEW CODE VVV why dont i copy ft_split edit it to use delimiters strch() instead of single delim char.
void	free_array(char **strs, int count)
{
	while (count--) free(strs[count]);
}

char	*malloc_len_or_until_chr(char *input, int *i, int len, char *chrs)
{
	char *ret;

	if (!len)
	{
		len = 0;
		while (input[*i + len] && !strchr(chrs, input[*i + len]))
			len++;
	}
	*i += len;
	ret = malloc(len + 1);
	if (ret)
	{
		printf("setting: `%.*s` with length %d\n", len, input[*i], len);
		memcpy(ret, input - len, len);
		ret[len] = 0;
	}
	return (ret);
}

#define SPLIT_ARRAY_STARTLEN 16
//returns true on err
char	**wordsplit(char *input, int len, int *splitcount)
{
	char **splitted;
	int	i;
	int	malloclen;

	splitted = NULL;
	*splitcount = 0;
	i = 0;
	malloclen = SPLIT_ARRAY_STARTLEN;
	while (input[++i])
	{
		if (*splitcount == malloclen || malloclen == SPLIT_ARRAY_STARTLEN)
		{
			malloclen *= 2;
			splitted = reallocarray(splitted, malloclen, sizeof(char *));
			if (splitted == NULL) return (NULL);
		}
		if (input[i] == '\'' && ++i)
			splitted[*splitcount] = malloc_len_or_until_chr(input, &i,  0, "'");
		else if (input[i] == '"' && ++i)
			splitted[*splitcount] = malloc_len_or_until_chr(input, &i,  0, "\"");
		else if (input[i] == '&' && ++i)
			splitted[*splitcount] = malloc_len_or_until_chr(input, &i,  0, "\"");
		else if (input[i] == '"' && ++i)
			splitted[*splitcount] = malloc_len_or_until_chr(input, &i,  0, "\"");
		else
			splitted[*splitcount] = malloc_len_or_until_chr(input, &i, 0, "|;& \t\n");
		if (splitted[*splitcount] == NULL)
			return (free_array(splitted, *splitcount), free(splitted), NULL);
		*splitcount += 1;
	}
	return (splitted);
}

int	main(int argc, char **argv)
{
	if (argc > 1 && ((argv[1][0] == '-' && argv[1][1] == 'h') || !strcmp("--help", argv[1])))
		return (printf("A simple program/shell to demonstrate pipes and control flow.\n"
				"Limited to /usr/bin/* programs.\n\n"
				"Usage: %s <command> [ [| && || ;] <command> ]\n", argv[0]), EXIT_SUCCESS);
	argv++;
	argc--;
	if (argc > 0) return (exec_all(argc, argv));
	char	*input = NULL;
	size_t	len = 0;
	char	**splitted = NULL;
	int		splitcount = 0;
	int		ret;

	while (1)
	{
		ret = getline(&input, &len, stdin);
		if (ret < 0)
			return (EXIT_FAILURE);
		else if (ret == 0)
			break ;

		splitted = wordsplit(input, len, &splitcount);
		if (splitted == NULL) return (free(input), EXIT_FAILURE);
		
		printf("Prepared Argv: [\n");
			for (int i = 0; i < splitcount; ++i) printf("\t`%s`, ", splitted[i]);
		printf("]\n");

		if (exec_all(splitcount, splitted))
			return (free_array(splitted, splitcount), free(splitted), free(input), EXIT_FAILURE);
	}
	free_array(splitted, splitcount);
	free(splitted);
	free(input);
	return (EXIT_SUCCESS);
}
