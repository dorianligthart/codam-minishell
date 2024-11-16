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

static void	set_token(char **line, t_input *input, int tok, size_t len)
{
	if (input->tokens != NULL)
	{
		input->tokens[input->total].id = tok;
		input->tokens[input->total].start = *line;
		input->tokens[input->total].len = len;
	}
	*line += len;
}

static void	set_a_bonus_token(char **line, t_input *input)
{
	if (**line == '(')
		set_token(line, input, PAREN_START, 1);
	else if (**line == ')')
		set_token(line, input, PAREN_END, 1);
	else if (**line == '{')
		set_token(line, input, PAREN_START, 1);
	else if (**line == '}')
		set_token(line, input, PAREN_END, 1);
	else if (**line == '[')
		set_token(line, input, PAREN_START, 1);
	else if (**line == ']')
		set_token(line, input, PAREN_END, 1);
	else if (**line == '&' && *line[1] == '&')
		set_token(line, input, CMD_AND, 2);
	else if (**line == '&')
		set_token(line, input, BACKGROUND, 1);
	else if (**line == '|' && *line[1] == '|')
		set_token(line, input, CMD_OR, 2);
	else if (**line == '*')
		set_token(line, input, WILDCARD, 1);
	else
		set_token(line, input, CMD,
				  len_until_delims(*line, " \t\n\v\r|<>$\'\"()&*="));
}

static void	set_a_token(char **line, t_input *input, bool *dquote)
{
	const char *delims = " \t\n\v\r|<>$\'\"()&*=";

	while (strchr(" \t\n\v\r", **line))
		++*line;
	if ((**line == '\"' && ++*line) || (*dquote == true && **line != '$'))
		set_token(line, input, STR, len_until_delims(*line, "\"$"));
	else if (**line == '\'' && ++*line)
		set_token(line, input, STR, len_until_delims(*line, "\'") + 1);
	else if (**line == '|' && *line[1] != '|')
		set_token(line, input, PIPE, 1);
	else if (**line == '<' && *line[1] == '<')
		set_token(line, input, DELIM_IN, 2); 
	else if (**line == '<')
		set_token(line, input, REDIRECT_IN, 1); 
	else if (**line == '>' && *line[1] == '>')
		set_token(line, input, APPEND_OUT, 2); 
	else if (**line == '>')
		set_token(line, input, REDIRECT_OUT, 1); 
	else if (**line == '$' && *line[1] == '?')
		set_token(line, input, EXITCODE, 2); 
	else if (**line == '$')
		set_token(line, input, VARNAME, len_until_delims(*line, delims));
	else if ('=' == (*line)[len_until_delims(*line, delims)])
		set_token(line, input, VARVALUE, len_until_delims(*line, delims));
	else
		set_a_bonus_token(line, input);
}

// returns token count or 0 if line is empty.
static void	tokenise(t_input *input, char *str)
{
	bool	instring;

	input->total = 0;
	while (*str)
	{
		if (*str == '\"' && str++)
		{
			instring = true;
			while (instring)
			{
				set_token(&str, input, STR, len_until_delims(str, "\"$") - 1);
				if (*str == '$' && ++input->total)
					set_token(&str, input, VARNAME,
							  len_until_delims(str, "\"$ \t\n\v\r") - 1);
				else
					instring = false;
			}
		}
		set_a_token(&str, input);
		if (input->tokens != NULL)
			input->tokens++;
		input->total++;
	}	
}

bool	ms_tokenise(t_input *input)
{
	input->tokens = NULL;
	tokenise(input, input->str);
	if (input->total == 0)
		return (false);
	input->tokens = malloc(input->total * sizeof(char));
	if (input->tokens == NULL)
		return (false);
	memset(input->tokens, '\0', sizeof(t_token) * input->total);
	tokenise(input, input->str);
	return (true);
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
