#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

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
	VAR,			//"$..." or just "..." before ASSIGN("...=").
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
	BLOCK_START,	//"["] = ""
	BLOCK_END,		//"]"
	CMD_AND,		//"&&"
	CMD_OR,			//"||"
	WILDCARD,		//"*"
};

typedef struct t_token
{
	int		id;
	char	*start;
	size_t	len;
} t_token;

typedef struct t_input
{
	char	*str;
	size_t	len;
	t_token	*tokens;
	size_t	total;
	size_t	current;
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

//const char	*builtins[BI_TOTAL] = {
//	[BI_ECHO] = "echo",
//	[BI_CD] = "cd",
//	[BI_PWD] = "pwd",
//	[BI_EXPORT] = "export",
//	[BI_UNSET] = "unset",
//	[BI_ENV] = "env",
//	[BI_EXIT] = "exit",
//};

char			*ms_read_stdin(void);
t_input			*ms_get_input(char *line);

//runcmd:
int	ms_runcmd(t_input *h);
int run_cmd();
int run_echo();
int run_cd();
int run_pwd();
int run_export();
int run_unset();
int run_env();
int run_exit();

//returns the length until a delimiter in delims is reached or zero.
size_t	len_until_delims(char *str, const char *delims);


#endif
