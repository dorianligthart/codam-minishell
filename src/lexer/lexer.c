/*
static int	ms_tokenise_3_2_1_or_0_chars(char **buf, unsigned char *table)
{
	unsigned char	t;
	char			c1;
	char			c2;

	c1 = (*buf)[1];
	c2 = (*buf)[(c1 != 0) * 2];
	if (c1 != 0 && c2 != 0
		&& table[ms_shrinkc(**buf) * 10000
				+ ms_shrinkc(c1) * 100 + ms_shrinkc(c2)])
		return (table[ms_shrinkc(**buf) * 10000
					 + ms_shrinkc(c1) * 100 + ms_shrinkc(c2)]);
	else if (c1 != 0 && table[ms_shrinkc(**buf) * 10000
							+ ms_shrinkc(c1) * 100])
		return (table[ms_shrinkc(**buf) * 10000 + ms_shrinkc(c1) * 100]);
	else
		return (table[ms_shrinkc(**buf) * 10000]);
	return ((int)"unreachable");
}

//in_dquote = (*str == '\"' && str++ && in_dquote == false);
//nesting means 
static void	ms_tokenise_set(t_input *input, char *str)
{
	while (*str)
	{
		if (input->tokens != NULL)
			input->tokens++;
		input->tokencount++;
	}
}

//may fail on malloc(3)
bool	ms_tokenise(t_input *input)
{
	unsigned char	table[1000000];
	const char		*builtins_4andlonger[5] = {
						"export", "unset", "exit", "echo", NULL};
	size_t			d;

	memset(table, '\0', MS_CHARS_3);
	if (TOKENS_SIZE < 1 || input)
		return (false);
	input->tokens_size = TOKENS_SIZE;
	input->tokens = malloc(TOKENS_SIZE * sizeof(t_token));
	if (input->tokens == NULL)
		return (false);
	memset(input->tokens, '\0', sizeof(t_token) * TOKEN_SIZE);
	memset(table, '\0', 128 * 128);
	set_table(table);
	ms_tokenise_set(input, input->buf);
	ms_tokenise_set(input, input->buf);
	return (true);
}
*/

/////////////////////////////////////////////////////////////////
/// old code ^^		new code vv
/////////////////////////////////////////////////////////////////

//#include <stdio.h>
//#include <unistd.h>
//#include <stdbool.h>
//#include <ctype.h> //isalnum()

#include <stdlib.h> //malloc()
#include <string.h> //memset() bzero()
#include "lexer.h"
#include "utils.h"
#include "minishell.h"

static bool	choose_wordtoken(char *str, size_t *i, t_lexer *l, size_t current)
{
	(void)str;
	(void)i;
	(void)l;
	(void)current;
	return (true);
}

static bool	set_token(char *str, size_t *i, t_lexer *l, size_t current)
{
	if (l->table[str[*i] * 128 + str[*i + 1]] != 0)
	{
		l->tokens[current].id = l->table[str[*i] * 128 + str[*i + 1]];
		l->tokens[current].start = (*i)++;
		l->tokens[current].end = (*i)++;
	}
	else if (l->table[str[*i] * 128] != 0)
	{
		l->tokens[current].id = l->table[str[*i] * 128];
		l->tokens[current].start = *i;
		l->tokens[current].end = (*i)++;
	}
	else
		return (choose_wordtoken(str, i, l, current));
	return (true);
}

//static_assert(TOKEN_COUNT == 22, "update/add tokens in prepare_table()");
bool	ms_initlexer(t_lexer *l)
{
	if (ms_expand_array((void **)&l->tokens, (void *)&l->tokens_size,
	                     sizeof(t_token), MS_TOKEN_SIZE) == false)
		return (false);
	memset(&l->table, 0, 128 * 128);
	l->table['\n' * 128] = TOKEN_NL;
	l->table[';'  * 128] = TOKEN_END;
	l->table['&'  * 128] = TOKEN_BG;
	l->table['|'  * 128] = TOKEN_PIPE_OUT;
	l->table['<'  * 128] = TOKEN_REDIRECT_IN;
	l->table['>'  * 128] = TOKEN_REDIRECT_OUT;
	l->table['/'  * 128] = TOKEN_FILE;
	l->table['*'  * 128] = TOKEN_FILENAME_EXPAN;
	l->table['\'' * 128] = TOKEN_SQUOTE; 
	l->table['"'  * 128] = TOKEN_DQUOTE;
	l->table['='  * 128] = TOKEN_PARAM_ASSIGN;
	l->table['$'  * 128] = TOKEN_PARAM_EXPAN;
	l->table['&'  * 128 + '&'] = TOKEN_AND;
	l->table['|'  * 128 + '|'] = TOKEN_OR;
	l->table['$'  * 128 + '\''] = TOKEN_CQUOTE;
	l->table['|'  * 128 + '&'] = TOKEN_PIPE_OUT_AND_ERR;
	l->table['<'  * 128 + '<'] = TOKEN_HERE_DOCUMENT;
	l->table['>'  * 128 + '>'] = TOKEN_REDIRECT_APPEND;
	l->table['$'  * 128 + '?'] = TOKEN_EXITCODE;
	l->table['$'  * 128 + '$'] = TOKEN_PID;
	l->table['.'  * 128 + '/'] = TOKEN_FILE;
	return (true);
}

bool	ms_lex(t_lexer *l, char *input)
{
	size_t	current;
	size_t	i;

	current = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (current == l->tokens_size)
			ms_expand_array((void **)&l->tokens,
			                (void *)&l->tokens_size,
							sizeof(t_token),
			                l->tokens_size + MS_TOKEN_SIZE);
		if (set_token(input, &i, l, current++) == false)
			return (false);
		i++;
	}
	return (true);
}

