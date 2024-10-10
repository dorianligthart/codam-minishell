// main loop prototype!

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	run_multiple(char *str, char *argv[])
{
	//fork and such :_)
}

int	main(int argc, char *argv[])
{
	char	*test = "/usr/bin/echo";
	
	if (argc < 2)
		printf("provide your command!\n");
	else
	{
		argc--;
		*argv = test;
		if (strchr(*argv, '|'))
			run_multiple(*argv, argv);
		else
			execve(test, argv, NULL);
	}
	return (0);
}
