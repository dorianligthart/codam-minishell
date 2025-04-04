#include "envs.h"
#include "utils.h"
#include "hash.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

bool	ms_unsetenv(t_environ *env, char *id)
{
	(void)id;
	(void)env;
	return (true);
}

bool	ms_setenv_str(t_environ *env, char *str)
{
	(void)str;
	(void)env;
	return (true);
}

//if hash hits 3rd time, try different seed 3 times, otherwise expand.
bool	ms_setenv(t_environ *env, char *id, char *val)
{
	(void)id;
	(void)val;
	(void)env;
	return (true);
}

static char	*ms_getenv_iter(char *id, t_environ *env)
{
	size_t	len;
	size_t	i;

	len = strlen(id);
	i = 0;
	while (env->ptr[i] != NULL)
	{
		if (strncmp(env->ptr[i], id, len) == 0)
			return (env->ptr[i]);
		i++;
	}
	return (NULL);
}

//TODO: hash algo LOL
char	*ms_getenv(char *id, t_environ *loc, t_environ *exp)
{
	char	*tmp;

	tmp = ms_getenv_iter(id, exp);
	if (tmp == NULL)
		tmp = ms_getenv_iter(id, loc);
	return (tmp);
}

