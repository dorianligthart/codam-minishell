#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>
#include "envs.h"
#include "prompt.h"
#include "lexer.h"
#include "parser.h"

typedef struct t_info
{
	char		**argv;
	int			argc;
	const char	*empty_string;
	int			current_command;
} t_info;

typedef struct t_shell
{
	t_info		info;
	t_environ	env;
	t_prompt	ps1;
	t_prompt	ps2;
	char 		*cmdstr;
	size_t		cmdsize;
	t_lexer		lexer;
	t_parser	parser;
} t_shell;

#endif //#define MINISHELL_H
