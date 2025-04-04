#include "envs.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//expands env to hold newsize amount of items.
bool	ms_env_realloc(t_environ *env, size_t ptrsize)
{
	char		**ptr;
	bool		*ismalloced;
	size_t		hashsize = ptrsize * 4;
	uint32_t	*hashptr;
	uint32_t	*hashptr2;

	ptr = malloc(sizeof(char *) * ptrsize);
	ismalloced = malloc(sizeof(bool) * ptrsize);
	hashptr = malloc(sizeof(uint32_t) * hashsize);
	hashptr2 = malloc(sizeof(uint32_t) * hashsize);
	if (ptr == NULL || ismalloced == NULL ||hashptr == NULL ||hashptr2 == NULL)
		return (false);

	bzero(ptr, ptrsize);
	bzero(ismalloced, ptrsize);
	bzero(hashptr, hashsize);
	bzero(hashptr2, hashsize);

	if (env->ptr != NULL)
	{
		memcpy(ptr, env->ptr, env->ptrsize);
		memcpy(ismalloced, env->ismalloced, env->ptrsize);
		memcpy(hashptr, env->hashptr, env->hashsize);
		memcpy(hashptr2, env->hashptr2, env->hashsize);
		free(env->ptr);
		free(env->ismalloced);
		free(env->hashptr);
		free(env->hashptr2);
	}

	env->ptrsize = ptrsize;
	env->hashsize = hashsize;
	env->ptr = ptr;
	env->ismalloced = ismalloced;
	env->hashptr = hashptr;
	env->hashptr2 = hashptr2;
	env->hashsize = hashsize;
	return (true);
}

extern char **environ;

bool	ms_env_init(t_environ *env, bool copyenviron)
{
	size_t	count;

	count = 0;
	if (copyenviron == true)
		while (environ[count] != NULL)
			count++;
	else
		count = MS_ENVSIZE;
	count = ms_round_to_pow_2(count);
	return (ms_env_realloc(env, count));
}

