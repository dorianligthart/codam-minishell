#include "lexer.h"
#include <stdio.h>

const char *token_id_str[TOKEN_COUNT] = {
	"token_undef", "token_nl", "token_and", "token_or", "token_end", "token_bg",
	"token_pipe_out", "token_pipe_out_and_err", "token_exe_undef", "token_exe",
	"token_squote", "token_dquote", "token_cquote", "token_param_assign",
	"token_param_expan", "token_redirect_in", "token_redirect_out",
	"token_here_document", "token_redirect_append", "token_filename_expan",
	"token_exitcode", "token_pid",
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

