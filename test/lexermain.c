#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct t_test
{
	const char	*string;
	t_token		tokens[4];
} t_test;

t_test tests[] = {
	{
		.string = "var=123\n",
		.tokens = {
			{
				.id = TOKEN_PARAM_ASSIGN,
				.begin = 0,
				.end = 3,
			}, {
				.id = TOKEN_WORD,
				.begin = 4,
				.end = 6,
			}, {
				.id = TOKEN_NL,
				.begin = 7,
				.end = 7,
			}
		} 
	}, {
		.string = "hello world\n",
		.tokens = {
			{
				.id = TOKEN_UNDEFINED,
				.begin = 0,
				.end = 4,
			}, {
				.id = TOKEN_UNDEFINED,
				.begin = 6,
				.end = 10,
			}, {
				.id = TOKEN_NL,
				.begin = 11,
				.end = 11,
			}
		} 
	}
};

int	main2(int argc, const char *argv[], const char **token_id_str)
{
	t_lexer	l;

	bzero(&l, sizeof(t_lexer));
	if (argc != 2) {
		for (size_t i = 0; i < sizeof(tests)/sizeof(*tests); ++i)
		{
			if (ms_lexer(&l, (char *)tests[i].string) == false)
				return (false);
			free(l.tokens);
			bzero(&l, sizeof(t_lexer));
		}
		return (0);
	}
	if (ms_lexer(&l, (char *)argv[1]) == false) return (1);
	for (size_t i = 0; i < l.size; ++i)
	{
		int		id = l.tokens[i].id;
		size_t	begin = l.tokens[i].begin;
		size_t	end = l.tokens[i].end;
		printf("'%.*s' = %s\n", (int)(end - begin), argv[1] + begin, token_id_str[id]);
	}
	return (0);
}

/*
./lexer 'echo \'Hello World\' '
./lexer 'HELLO=WORLD'
*/
int	main(int argc, const char *argv[])
{
	const char *token_id_str[TOKEN_COUNT] = {
		[TOKEN_UNDEFINED]        = "undefined",
		[TOKEN_WORD]             = "word",
		[TOKEN_NL]               = "nl",
		[TOKEN_AND]= "and", [TOKEN_OR] = "or", 
		[TOKEN_END]= "end", [TOKEN_BG] = "bg",
		[TOKEN_PIPE_OUT]         = "pipe_out",
		[TOKEN_PIPE_OUT_AND_ERR] = "pipe_out_and_err",
		[TOKEN_FILE]             = "file",
		[TOKEN_SQUOTE]           = "squote",
		[TOKEN_DQUOTE]           = "dquote",
		[TOKEN_CQUOTE]           = "cquote",
		[TOKEN_PARAM_ASSIGN]     = "param_assign",
		[TOKEN_PARAM_EXPAN]      = "param_expan",
		[TOKEN_REDIRECT_IN]      = "redirect_in",
		[TOKEN_REDIRECT_OUT]     = "redirect_out",
		[TOKEN_HERE_DOCUMENT]    = "here_document",
		[TOKEN_REDIRECT_APPEND]  = "redirect_append",
		[TOKEN_FILENAME_EXPAN]   = "filename_expan",
		[TOKEN_EXITCODE]         = "exitcode",
		[TOKEN_PID]              = "pid"};

	return (main2(argc, argv, token_id_str));
}

