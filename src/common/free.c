#include "minishell.h"
#include <stdlib.h>

void free_env(t_environ *env)
{
	size_t	i;

	if (env->ismalloced != NULL && env->ptr != NULL)
	{
		i = 0;
		while (env->ptr[i] != NULL)
		{
			if (env->ismalloced[i] == true)
				free(env->ptr[i]);
			++i;
		}
	}
	if (env->ptr != NULL)
		free(env->ptr);
	if (env->ismalloced != NULL)
		free(env->ismalloced);
	if (env->islocal != NULL)
		free(env->islocal);
	if (env->table1 != NULL)
		free(env->table1);
	if (env->table2 != NULL)
		free(env->table2);
	if (env->table3 != NULL)
		free(env->table3);
}

void	ms_free(t_shell *sh)
{
	free_env(&sh->env);
	if (sh->ps1.size != 0)
		free(sh->ps1.str);
	if (sh->ps2.size != 0)
		free(sh->ps2.str);
	if (sh->cmdsize != 0)
		free(sh->cmdstr);
	if (sh->lexer.tokens_size != 0)
		free(sh->lexer.tokens);
}

