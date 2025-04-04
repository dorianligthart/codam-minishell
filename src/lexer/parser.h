#ifndef MS_PARSER_H
#define MS_PARSER_H

#include <stdbool.h>

typedef struct t_parser
{
	int	unimplemented;
} t_parser;

typedef struct t_lexer t_lexer;

bool	ms_parser_init(t_parser *parser);
bool	ms_parser_go(t_parser *parser, t_lexer *lexer);

#endif //#ifndef MS_PARSER_H
