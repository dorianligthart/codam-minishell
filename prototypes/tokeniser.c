//UNNEEDED FOR THIS PROJECT:
//	keywords: [if|then|else|elif|fi|for|while|do|done|case|esac
//		 		|echo|export|unset|return|break|continue]
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

//you should merge CMD and BUILTIN_* but for the scope of this project its fine.
enum e_tokens
{
	NONE = 0,
	FINISHED,
	CMD,			//seq of printable characters (no $<>|)
	CMD_OPTION,
	SQUOTES,
	DQUOTES,
	EXITCODE,		//"$?"
	ENV_VAR,		//"$..."
	EQUAL,
	REDIRECT_IN,	//"<"
	REDIRECT_OUT,	//">"
	DELIM_IN,		//"<<"
	APPEND_OUT,		//">>"
	PIPE,			//"|"
	BUILTIN_ECHO,
	BUILTIN_ECHO_N,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	TOTAL,
};

//checking fixed_length will determine if start and end are set.
typedef struct t_token
{
	int		id;
	char	*start;
	char	*end;
} t_token;

size_t	len_until_delim(char *line, const char *delims)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (line[y])
	{
		x = 0;
		while (delims[x])
		{
			if (line[y] == delims[x])
				return (y);
			x++;
		}
		y++;
	}
	return y;
}

void	set_token(char **line, t_token *token, int t, size_t len)
{
	if (token != NULL)
	{
		token->id = t;
		token->start = *line;
		token->end = *line + len;
	}
	*line += len;
}

	//TODO: double quotes environment variables. and escape sequences.
void	set_token_str(char **line, t_token *token)
{
	set_token(line, token, DQUOTES, len_until_delim(*line, "\""));
}

	//write(1, "REACHED\n", 8);
void	set_a_builtin_token(char **line, t_token *token, const char *delims)
{
	if (strncmp(*line, "echo", 4) == 0)
		set_token(line, token, BUILTIN_ECHO, 4);
	else if (strncmp(*line, "cd", 2) == 0)
		set_token(line, token, BUILTIN_CD, 2);
	else if (strncmp(*line, "pwd", 3) == 0)
		set_token(line, token, BUILTIN_PWD, 3);
	else if (strncmp(*line, "export", 6) == 0)
		set_token(line, token, BUILTIN_EXPORT, 6);
	else if (strncmp(*line, "unset", 5) == 0)
		set_token(line, token, BUILTIN_UNSET, 5);
	else if (strncmp(*line, "env", 3) == 0)
		set_token(line, token, BUILTIN_ENV, 3);
	else if (strncmp(*line, "exit", 4) == 0)
		set_token(line, token, BUILTIN_EXIT, 4);
	else if (strncmp(*line, "-", 1) == 0)
		set_token(line, token, CMD_OPTION,
				  len_until_delim(*line, delims));
//	else
//		printf("invalid string: '%s'\n", *line), exit(1);
}

void	set_a_token(char **line, t_token *token)
{
	const char *delims = "|<>$ \t\n\v\r";

	while (strchr(" \t\n\v\r", **line))
		++*line;
	if (**line == '\'' && *(++*line))
		set_token(line, token, SQUOTES, len_until_delim(*line, "\'"));
	else if (**line == '\"' && *(++*line))
		set_token_str(line, token);
	else if (**line == '|')
		set_token(line, token, PIPE, 1);
	else if (**line == '<' && *line[1] == '<')
		set_token(line, token, DELIM_IN, 2); 
	else if (**line == '<')
		set_token(line, token, REDIRECT_IN, 1); 
	else if (**line == '>' && *line[1] == '>')
		set_token(line, token, APPEND_OUT, 2); 
	else if (**line == '>')
		set_token(line, token, REDIRECT_OUT, 1); 
	else if (**line == '$' && *line[1] == '?')
		set_token(line, token, EXITCODE, 2); 
	else if (**line == '$')
		set_token(line, token, ENV_VAR, len_until_delim(*line, delims));
	else
		set_a_builtin_token(line, token, delims);
}

//returns token amount in line or 0 on error.
size_t	tokenise(char *line, t_token *token)
{
	size_t	tokencount = 0;

	while (*line)
	{
		set_a_token(&line, token);
		if (token != NULL)
			token++;
		tokencount++;
	}	
	return tokencount;
}

void	printtokens(t_token *token, size_t tokencount)
{
	size_t	i;

	printf("TOKENS[");
	i = 0;
	while (i < tokencount)
	{
		if (token[i].id == SQUOTES)
			printf("SQUOTES");
		if (token[i].id == DQUOTES)
			printf("DQUOTES");
		if (token[i].id == EXITCODE)
			printf("EXITCODE");
		if (token[i].id == ENV_VAR)
			printf("ENV_VAR");
		if (token[i].id == REDIRECT_IN)
			printf("REDIRECT_IN");
		if (token[i].id == REDIRECT_OUT)
			printf("REDIRECT_OUT");
		if (token[i].id == DELIM_IN)
			printf("DELIM_IN");
		if (token[i].id == APPEND_OUT)
			printf("APPEND_OUT");
		if (token[i].id == PIPE)
			printf("PIPE");
		if (token[i].id == BUILTIN_ECHO)
			printf("ECHO");
		if (token[i].id == BUILTIN_ECHO_N)
			printf("ECHO_N");
		if (token[i].id == BUILTIN_CD)
			printf("CD");
		if (token[i].id == BUILTIN_PWD)
			printf("PWD");
		if (token[i].id == BUILTIN_EXPORT)
			printf("EXPORT");
		if (token[i].id == BUILTIN_UNSET)
			printf("UNSET");
		if (token[i].id == BUILTIN_ENV)
			printf("ENV");
		if (token[i].id == BUILTIN_EXIT)
			printf("EXIT");
		printf(", ");
		i++;
	}
	printf("]\n");
}

void	test(char *line)
{
	t_token	*tokens;
	size_t	tokencount;

	tokencount = tokenise(line, NULL);
	tokens = malloc(tokencount * sizeof(char));
	if (!tokens)
		return ;
	memset(tokens, '\0', sizeof(t_token) * tokencount);
	tokenise(line, tokens);
	printtokens(tokens, tokencount);
}

int		main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	test("echo hello world :)");
	//test("echo \"hello world :)\"");
	test("echo -n ");
	test("echo \"");
	return (0);
}
