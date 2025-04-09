#ifndef MS_PROMPT_H
# define MS_PROMPT_H

#ifndef MS_PS1_DEFAULT_STR 
#define MS_PS1_DEFAULT_STR "PS1=\\s-\\v\\$ "
#endif

//PS2 is invoked when a token that has to close didn't close, or with here_doc.
//unlike bash, '\o' can print the 'open' token it's looking for,
//strings, subshell, or even 'if' statements and pipes.
#ifndef MS_PS2_DEFAULT_STR 
#define MS_PS2_DEFAULT_STR "PS2=> "
#endif

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
