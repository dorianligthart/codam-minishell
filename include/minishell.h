#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdbool.h>

//#include <stdio.h> //global pointer to environment variables.
//extern char **environ;

#if defined(STDIN) || defined(STDOUT) || defined(STDERR)
#else
# define STDIN 0
# define STDOUT 1
# define STDERR 2
#endif

enum e_tokenid
{
	NONE = 0,
	CMD,			//seq of printable characters, including builtins!
	STR,			//determined by quotes, after command, or after ASSIGN.
	VARNAME,		//"$..." or just "..." before ASSIGN("...=").
	VARVALUE,		//
	ASSIGN,			//"="
	EXITCODE,		//"$?"
	REDIRECT_IN,	//"<"
	REDIRECT_OUT,	//">"
	DELIM_IN,		//"<<"
	APPEND_OUT,		//">>"
	PIPE,			//"|"
	//bonus:
	CURLY_START,	//"{"
	CURLY_END,		//"}"
	PAREN_START,	//"("
	PAREN_END,		//")"
	BLOCK_START,	//"["
	BLOCK_END,		//"]"
	CMD_AND,		//"&&"
	CMD_OR,			//"||"
	WILDCARD,		//"*"
	BACKGROUND,		//"&"
};

typedef struct t_token
{
	int		id;
	char	*start;
	size_t	len;
} t_token;

////stuff i might need
//enum e_astnodetypes
//{
//	AST_TYPE_COUNT,
//}
//typedef struct t_astcmd
//{
//	char		*str;
//	size_t		length;
//	t_astnode	*parent;
//	t_astnode	*child;
//} t_astcmd;
//size_t	len_until_delims(char *str, const char *delims);

typedef struct t_input
{
	char		*str;
	size_t		bufsize;
	size_t		strlen;
	t_token		*tokens;
	size_t		total;
	t_token		*parsed;
} t_input;

enum	e_builtins
{
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	BI_TOTAL,
};

//main functions:
char	*ms_read_stdin(void);
bool	ms_tokenise(t_input *input);
bool	ms_expand_envs(t_input *input);
bool	ms_create_ast(t_input *input);
bool	ms_exec(t_input *input, int argc, char **argv, char **envp);
int 	bi_echo();
int 	bi_cd();
int 	bi_pwd();
int 	bi_export();
int 	bi_unset();
int 	bi_env();
int 	bi_exit();

//AST functions:



#endif
