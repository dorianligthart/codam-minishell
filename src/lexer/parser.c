//standard:
#include <stdbool.h>
#include <stdio.h>

//local:
#include "parser.h"
#include "lexer.h"

bool	ms_initparser(t_parser *parser)
{
	//fprintf(stderr, "\nms_parser_init() not implemented!\n");
	(void)parser;
	return (true);
}

bool	ms_parse(t_parser *parser, t_lexer *lexer)
{
	printf("[INFO] ms_parse() retrieved: lexer [\n\ttokens_len = %zu\n\ttokens_size = %zu\n\ttokens = %p\n]", lexer->tokens_len, lexer->tokens_size, lexer->tokens);
	//fprintf(stderr, "\nms_parser() not implemented!\n");
	(void)parser;
	(void)lexer;
	return (true);
}

