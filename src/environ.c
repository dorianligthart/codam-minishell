//functionality on top of src/env-get-set-unset.c
#include "environ.h"
#include "utils.h"
#include "hash.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//dont know what whether to implement these:
		//"CDPATH=",
		//"MAIL=",
		//"MAILPATH=",
		//"OPTARG=",
		//"OPTIND="
//https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Variables.html
bool	ms_setenv_bourne(t_environ *env)
{
	const char	*bourne[10] = {
		"PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:",
		"PS1=\\s-\\v\\$ ",
		"PS2=> ",
		"IFS= \t\n",
		"HOME=",
	};
	uint32_t		i;

	i = -1;
	while (i < 4)
		if (!ms_getenv((char *)bourne[i], env) && !ms_setenv((char **)&bourne[i], NULL, env, false))
		return (false);
	if (!ms_getenv((char *)bourne[++i], env) && !ms_setenv((char **)&bourne[i], NULL, env, false))
		return (false);
	return (true);
}

extern char **environ;

#include <assert.h>
bool	ms_initenv(t_environ *e)
{
	uint32_t	length;
	uint32_t	i;

	assert(MS_ENVSIZE > 1);
	e->envp = environ;
	length = 0;
	while (environ[length])
		length++;
	if (!ms_expand_array((void **)&e->vars, (void *)&e->size, (length / MS_ENVSIZE + 1) * MS_ENVSIZE))
		return (false);
	i = -1;
	while (environ && environ[++i])
		ms_setenv(&environ[i], NULL, e, false);
	return (true);
}

