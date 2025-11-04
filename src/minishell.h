#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h> //size_t

#include "argv.h" //t_info
#include "environ.h" //t_environ
#include "prompt.h" //t_prompt
#include "lexer.h" //t_lexer
#include "parser.h" //t_parser

typedef struct t_shell
{
	t_info		info;
	t_environ	envs;
	t_prompt	ps1;
	t_prompt	ps2;
	char 		*cmdstr;
	size_t		cmdsize;
	t_lexer		lexer;
	t_parser	parser;
} t_shell;

int	ms_getinput(t_shell *sh);

#endif //#define MINISHELL_H
