#ifndef MS_PROMPT_H
# define MS_PROMPT_H

#ifndef MS_PROMPT_SIZE
#define MS_PROMPT_SIZE 1024
#endif

typedef struct t_prompt
{
	char	*str;
	size_t	len;
	size_t	size;
	bool	regen;
} t_prompt;

typedef struct t_info t_info;

#include "minishell.h"
#include <stdbool.h>

bool	ms_prompt_update(t_info *info, t_prompt *p, char *new);

#endif //#ifndef MS_PROMPT_H
