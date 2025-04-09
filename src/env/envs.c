#include "envs.h"
#include "utils.h"
#include "hash.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef MS_HASHMULT
#define MS_HASHMULT 4
#endif

void	ms_unsetenv(char *str, t_environ *env)
{
	const size_t	len = ms_strchrlen(str, '=') % env->size * MS_HASHMULT;
	const uint32_t	hash = ms_hash(str, len, env->seed) % (env->size * MS_HASHMULT);

	if (env->table3[hash] != (uint32_t)-1)
	{
		env->ptr[env->table3[hash]] = NULL;
		env->table3[hash] = (uint32_t)-1;
	}
	else if (env->table2[hash] != (uint32_t)-1)
	{
		env->ptr[env->table2[hash]] = NULL;
		env->table2[hash] = (uint32_t)-1;
	}
	else if (env->table1[hash] != (uint32_t)-1)
	{
		env->ptr[env->table2[hash]] = NULL;
		env->table1[hash] = (uint32_t)-1;
	}
	else
		fprintf(stderr, "trying to unset '%.*s', but it doesnt exist dumbass lmao\n",\
				(int)len, str);
}

//assuming sizeof(p) == n * size
static void *ms_generic_memset(void *p, void *val, size_t size, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		memcpy(((char *)p + i * size), val, size);
	return (p);
}

static void	ms_regen_hashtable(t_environ *env)
{
	const uint32_t	val = -1;
	size_t			i;
	uint32_t		hash;

	ms_generic_memset(env->table1, (void *)&val, sizeof(val), env->size * MS_HASHMULT);
	ms_generic_memset(env->table2, (void *)&val, sizeof(val), env->size * MS_HASHMULT);
	ms_generic_memset(env->table2, (void *)&val, sizeof(val), env->size * MS_HASHMULT);
	env->seed++;
	i = -1;
	while (++i < (*env).size)
	{
		if (env->ptr[i] && env->ptr[i][0])
		{
			hash = ms_hash(env->ptr[i], ms_strchrlen(env->ptr[i], '='),
			               env->seed) % (env->size * MS_HASHMULT);
			if (env->table1[hash] == (uint32_t)-1)
				env->table1[hash] = i;
			else if (env->table2[hash] == (uint32_t)-1)
				env->table2[hash] = i;
			else if (env->table3[hash] == (uint32_t)-1)
				env->table3[hash] = i;
			else {env->seed++; i = 0; continue;}
		}
	}
}

bool	ms_setenv(char *str, t_environ *env, bool islocal)
{
	const size_t	len = ms_strchrlen(str, '=');
	const uint32_t	hash = ms_hash(str, len, env->seed) % (env->size * MS_HASHMULT);
	size_t			i;

	//TODO: ms_setenv(): implement resetting a variable;
	if ((env->ptr[env->table3[hash]] && strncmp(env->ptr[env->table3[hash]], str, len) == 0)
		|| (env->ptr[env->table2[hash]] && strncmp(env->ptr[env->table2[hash]], str, len) == 0)
		|| (env->ptr[env->table1[hash]] && strncmp(env->ptr[env->table1[hash]], str, len) == 0))
		return (printf("Error: ms_setenv() resetting a variable isn't implemented yet! '%.*s'\n", (int)len, str), false);
	i = -1;
	while (++i < (*env).size && env->ptr[i] != NULL)
		;
	if (i == env->size && ms_envrealloc(env, env->size * 2) == false)
		return (false);
	env->ptr[i] = str;
	if (env->table1[hash] && env->table2[hash] && env->table3[hash])
		ms_regen_hashtable(env);
	if (env->table1[hash] && env->table2[hash])
		env->table3[hash] = i;
	else if (env->table1[hash])
		env->table2[hash] = i;
	else
		env->table1[hash] = i;
	if (islocal == true)
		env->islocal[i] = true;
	return (true);
}

char	*ms_getenv(char *str, t_environ *env)
{
	const size_t	len = ms_strchrlen(str, '=');
	const uint32_t	hash = ms_hash(str, len, env->seed) % (env->size * MS_HASHMULT);

	if (env->table3[hash] != (uint32_t)-1)
		return (env->ptr[env->table3[hash]]);
	if (env->table2[hash] != (uint32_t)-1)
		return (env->ptr[env->table2[hash]]);
	if (env->table1[hash] != (uint32_t)-1)
		return (env->ptr[env->table1[hash]]);
	return (NULL);
}

