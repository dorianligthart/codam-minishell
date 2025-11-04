#ifndef MAXISHELL_H
#define MAXISHELL_H

enum e_tokenid_rest
{
	HIST_LAST,        //"!!"
	HIST_N,           //"!n"
	HIST_MINUS,       //"!-"
	HIST_STARTS_WITH, //"!string"
	HIST_ENDS,        //"!?string"
	HIST_CONTAINS,    //"!?string?"
	HIST_REPLACE,     //"^target^replacement"
	ESCAPE,           //"\"
	DQUOTE,           //"""
	SQUOTE,           //"'"
	CQUOTE,           //"$'", ANSI-C quoting converts to SQUOTE since it's const.
	COMMENT,          //"#...\n" interactive_comments enabled as flag.
	KEYWORD,          /*of the following:
	if   then elif   else   fi time
	for  in	  until  while  do done
	case esac coproc select function
	{    }    [[     ]]     !
	*/
	NEGATION,     //"![command|]"
	PIPE_OUT,     //"|"
	PIPE_OUT_ERR, //"|&"
	CMD_AND,      //"&&"
	CMD_OR,       //"||"
	CMD_END,      //";"
	CMD_BG,       //"&" // CMD terminates on ";&\n"
	GROUP_OLD,    //"{"
	GROUP_NEW,    //"("
	BRACE_EXPAN,  //"${"
	TILDE_EXPAN,  //"~" is set to $HOME
	ANSI_C,       //"$'"
	CMD_SUBST,    //"$("
	ARITH_EXPAN,  //"(("
	ARRAY,        //"=("
	PID,          //"$$"
	//patterns are in words that aren't quotes. that word is replaced by matches
	PATTERN_WILD, //"*"
	PATTERN_CHAR, //"?"
	PATTERN,      //"["
	//arithmetic between $(()) or $[]:
	UNARY_PLUS,     //"+"
	UNARY_MINUS,    //"-"
	ADD,            //"+"
	SUBTRACT,       //"-"
	MULTIPLY,       //"*"
	DIVIDE,         //"/"
	MODULO,         //"%"
	EXPONANT,       //"**"
	PRE_INCR,       //"--id"
	PRE_DECR,       //"--id"
	POST_INCR,      //"id++"
	POST_DECR,      //"id++"
	BIT_NEGATION,   //"~" ("!" = NEGATION)
	BIT_AND,        //"&"
	BIT_OR,         //"|"
	BIT_XOR,        //"^"
	BITSHIFT_RIGHT, //"-"
	BITSHIFT_LEFT,  //"-"
};

//booleans are mostly for declare builtin.
//bool	is_local; //non-interactive
typedef struct t_env
{
	char	*name;
	void	*value;
	bool	unset;
	bool	readonly;          //declare -r
	bool	exported;          //declare -x
	bool	integer;           //declare -i
	bool	array;             //declare -a
	bool	associative_array; //declare -A
	bool	reference;         //declare -n
} t_env;

#endif
