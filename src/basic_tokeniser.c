//UNNEEDED FOR THIS PROJECT:
//	BACKGROUND,		//"&"
//	KEYWORD,
//	PID,		//"$$"
//	ARGC,		//"$#" (array length)
//	ARGV_N,		//"$<NUMBER>" (array index)
//	ARGV,		//"$@" (array)
//	PARENTH_START,
//	PARENTH_END,
//	SQUARE_START,
//	SQUARE_END,
//	CURLY_START,
//	CURLY_END,
//	AND,			//"&&"
//	OR,				//"||"
//	WILDCARD,		//"*"
//	OPERATION,		//""
//	static const char	*keywords[27] = {"if", "then", "else", "elif", "fi",
//		"case", "esac", "for", "select", "while", "until", "do", "done",
//		"break", "continue", "function", "return", "local", "time", "in",
//		"export", "readonly", "declare", "let", "shift", "trap", "time", NULL};
	

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"

//returns 0 if delims wasn't found.
size_t	len_until_delims(char *str, const char *delims)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (str[y])
	{
		x = 0;
		while (delims[x])
		{
			if (str[y] == delims[x])
				return (y);
			x++;
		}
		y++;
	}
	return 0;
}

static void	set_token(char **line, t_input *h, int tok, size_t len)
{
	if (h->tokens != NULL)
	{
		h->tokens[h->current].id = tok;
		h->tokens[h->current].start = *line;
		h->tokens[h->current].len = len;
	}
	*line += len;
}

static void	set_a_bonus_token(char **line, t_input *header)
{
	if (**line == '(')
		set_token(line, header, PAREN_START, 1);
	else if (**line == ')')
		set_token(line, header, PAREN_END, 1);
	else if (**line == '&' && *line[1] == '&')
		set_token(line, header, CMD_AND, 2);
	else if (**line == '|' && *line[1] == '|')
		set_token(line, header, CMD_OR, 2);
	else if (**line == '*')
		set_token(line, header, WILDCARD, 1);
	else
		set_token(line, header, CMD,
				  len_until_delims(*line, " \t\n\v\r|<>$\'\"()&*="));
}
// beware: CMD could be ASSIGN.
static void	set_a_token(char **line, t_input *header)
{
	const char *delims = " \t\n\v\r|<>$\'\"()&*=";

	while (strchr(" \t\n\v\r", **line))
		++*line;
	if (**line == '\'' && ++*line)
		set_token(line, header, STR, len_until_delims(*line, "\'") + 1);
	else if (**line == '|' && *line[1] != '|')
		set_token(line, header, PIPE, 1);
	else if (**line == '<' && *line[1] == '<')
		set_token(line, header, DELIM_IN, 2); 
	else if (**line == '<')
		set_token(line, header, REDIRECT_IN, 1); 
	else if (**line == '>' && *line[1] == '>')
		set_token(line, header, APPEND_OUT, 2); 
	else if (**line == '>')
		set_token(line, header, REDIRECT_OUT, 1); 
	else if (**line == '$' && *line[1] == '?')
		set_token(line, header, EXITCODE, 2); 
	else if (**line == '$')
		set_token(line, header, VAR, len_until_delims(*line, delims));
	else if ('=' == (*line)[len_until_delims(*line, delims)])
		set_token(line, header, ASSIGN, len_until_delims(*line, delims));
	else
		set_a_bonus_token(line, header);
}

// returns token count or 0 if line is empty.
static size_t	tokenise(char *line, t_input *h)
{
	bool	instring;

	h->total = 0;
	while (*line)
	{
		if (*line == '\"' && line++)
		{
			instring = true;
			while (instring)
			{
				set_token(&line, h, STR, len_until_delims(line, "\"$") - 1);
				if (*line == '$' && ++h->total)
					set_token(&line, h, VAR,
							  len_until_delims(line, "\"$ \t\n\v\r") - 1);
				else
					instring = false;
			}
		}
		set_a_token(&line, h);
		if (h->tokens != NULL)
			h->tokens++;
		h->total++;
	}	
	return h->total;
}

t_input	*ms_get_tokens(char *line)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (input == NULL)
		return (NULL);
	input->tokens = NULL;
	input->total = tokenise(line, input);
	if (input->total == 0)
		return (NULL);
	input->tokens = malloc(input->total * sizeof(char));
	if (!input->tokens)
		return NULL;
	memset(input->tokens, '\0', sizeof(t_token) * input->total);
	tokenise(line, input);
	return (input);
}

//int		main(int argc, char *argv[])
//{
//	(void)argc;
//	(void)argv;
//	test("echo hello world :)");
//	//test("echo \"hello world :)\"");
//	test("echo -n ");
//	test("echo \"");
//	return (0);
//}
