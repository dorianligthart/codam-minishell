#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

ssize_t	envpath_count(const char *envpath)
{
	ssize_t	res;
	ssize_t	ui;

	if (envpath == NULL || *envpath == '\0')
		return (-1);
	res = 1;
	ui = 0;
	while (envpath[ui] != '\0' && envpath[ui] != ':')
	{
		if (envpath[ui + 1] == ':')
		{
			if (envpath[ui + 2] == ':')
				return (-1);
			ui++;
			res++;
		}
		ui++;
	}
	return (res);
}

void freefunc(char **str, size_t count)
{
	while (count--)
		free(str + count);
}

ssize_t	set_cmd(char **paths, char *envpath, size_t count, char *cmd)
{
	size_t	ui;
	size_t	subpathlen;

	*paths = malloc(count * sizeof(char *));
	if (paths == NULL)
		return (1);
	ui = 0;
	while (ui < count)
	{
		subpathlen = NULL ;
		paths[ui] = malloc(1);
		if (path[ui] == NULL)
			return (freefunc(paths, ui), false);
	}
	return (true);
}

int main (void)
{
	char	*cmd = "ls";
	char	*envpath = getenv("PATH");
	char	*paths;
	ssize_t	envpathcount;

	envpathcount = envpath_count(envpath);
	printf("envpath_count:%zi\n", envpathcount);
	if (set_cmd(&paths, envpath, envpathcount, cmd) == false)
		return (1);
	return 0;
}
