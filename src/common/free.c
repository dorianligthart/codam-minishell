#include "minishell.h"
#include <stdlib.h>

void free_env(t_environ *env)
{
	size_t	i;

	if (env->ismalloced != NULL && env->ptr != NULL)
	{
		i = 0;
		while (env->ptr[i] != NULL)
			if (env->ismalloced[i] == true)
				free(env->ptr[i++]);
	}
	if (env->ptr != NULL)
		free(env->ptr);
	if (env->ismalloced != NULL)
		free(env->ismalloced);
	if (env->hashptr != NULL)
		free(env->hashptr);
	if (env->hashptr2 != NULL)
		free(env->hashptr2);
}

void	ms_free(t_shell *sh)
{
	free_env(&sh->loc_env);
	free_env(&sh->exp_env);
	if (sh->ps1.size != 0)
		free(sh->ps1.str);
	if (sh->ps2.size != 0)
		free(sh->ps2.str);
	if (sh->cmdsize != 0)
		free(sh->cmdstr);
	if (sh->lexer.tokens != NULL)
		free(sh->lexer.tokens);
}

