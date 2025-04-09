#ifndef MS_LEXER_H
# define MS_LEXER_H

/* NOTES:
word: starts with [A-Za-z_] and could continue with [A-Za-z_0-9].
special tokens:
	CMD_EXPLICIT = "./path" or "/path"
	CMD          = "path" 
	CQUOTE       = "$'"
	PARAM_ASSIGN = "word="
	PARAM_EXPAN  = "$word"
	FILE_EXPAN   = "*"
BI_ = builtin
CO_ = control operator = \n && || ; & | |& ( )
*/

//start buffer size of token array.
#ifndef MS_TOKEN_SIZE
# define MS_TOKEN_SIZE 64
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MS_METACHARS "|&;()<>"

//control tokens: [\n, &&, ||, ;, &, |, |&]
//redirect tokens: [<, >, <<, >>]
enum e_tokenid
{
	TOKEN_UNDEF = 0,
	TOKEN_NL,				//is `\n`
	TOKEN_AND,				//is `&&`
	TOKEN_OR,				//is `||`
	TOKEN_END,				//is `;`
	TOKEN_BG,				//is `&`
	TOKEN_PIPE_OUT,			//is `|`
	TOKEN_PIPE_OUT_AND_ERR,	//is `|&`
	TOKEN_FILE_UNDEF,		//word (search in $PATH)
	TOKEN_FILE,				//starts with `./` or `/`
	TOKEN_SQUOTE,			//starts with `'` ends with `'`
	TOKEN_DQUOTE,			//starts with `"` ends with `"`
	TOKEN_CQUOTE,			//starts with `$'` ends with `'`
	TOKEN_PARAM_ASSIGN, 	//is `word=...`
	TOKEN_PARAM_EXPAN,		//is `$word`
	TOKEN_REDIRECT_IN,		//is `<`
	TOKEN_REDIRECT_OUT,		//is `>`
	TOKEN_HERE_DOCUMENT,	//is `<<`
	TOKEN_REDIRECT_APPEND,	//is `>>`
	TOKEN_FILENAME_EXPAN,	//is `*`
	TOKEN_EXITCODE,			//is `$?`
	TOKEN_PID,				//is `$$`
	TOKEN_COUNT,
};

typedef struct t_token
{
	uint8_t	id;
	size_t	start;
	size_t	end;
} t_token;

//table = 128 * 128 for the first 2 characters.
typedef struct t_lexer
{
	t_token	*tokens;
	size_t	tokens_len;
	size_t	tokens_size;
	uint8_t	table[128 * 128];
} t_lexer;

bool	ms_initlexer(t_lexer *lexer);
bool	ms_lex(t_lexer *l, char *input);

#endif //#ifndef MS_LEXER_H
