#include "lexer.h"
#include <stdio.h>

const char *token_id_str[TOKEN_COUNT] = {
	[TOKEN_UNDEF] = "token_undef", [TOKEN_NL] = "token_nl",
	[TOKEN_AND] = "token_and", [TOKEN_OR] = "token_or", 
	[TOKEN_END] = "token_end", [TOKEN_BG] = "token_bg",
	[TOKEN_PIPE_OUT] = "token_pipe_out",
	[TOKEN_PIPE_OUT_AND_ERR] = "token_pipe_out_and_err",
	[TOKEN_FILE_UNDEF] = "token_file_undef", [TOKEN_FILE] = "token_file",
	[TOKEN_SQUOTE] = "token_squote", [TOKEN_DQUOTE] = "token_dquote",
	[TOKEN_CQUOTE] = "token_cquote",
	[TOKEN_PARAM_ASSIGN] = "token_param_assign",
	[TOKEN_PARAM_EXPAN] = "token_param_expan",
	[TOKEN_REDIRECT_IN] = "token_redirect_in",
	[TOKEN_REDIRECT_OUT] = "token_redirect_out",
	[TOKEN_HERE_DOCUMENT] = "token_here_document",
	[TOKEN_REDIRECT_APPEND] = "token_redirect_append",
	[TOKEN_FILENAME_EXPAN] = "token_filename_expan",
	[TOKEN_EXITCODE] = "token_exitcode", [TOKEN_PID] = "token_pid",
};

/*
./lexer 'echo \'Hello World\' '
./lexer 'HELLO=WORLD'
*/
int	main(int argc, const char *argv[])
{
	t_lexer	l;

	if (argc != 2) {
		printf("Error: lexer test expects 1 argument\n");
		return (1);
	}
	if (ms_lexer(&l, argv[1]) == false) return (1);
	for (size_t i = 0; i < l.tokens_len; ++i)
	{
		int		id = l.tokens[i].id;
		size_t	start = l.tokens[i].start;
		size_t	end = l.tokens[i].end;
		printf("'%.*s' = %s\n", end - start, argv[1][start], token_id_str[id]);
	}
	return (0);
}

