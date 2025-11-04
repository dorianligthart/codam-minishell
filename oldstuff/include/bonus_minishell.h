//See BASH-INTERACTIVE.md for more bash info.
//#include <stdio.h> //global pointer to environment variables.
//extern char **environ;

//{} BRACE expansion syntax:
// x{1..3}y : x1y x2y x3y
//
//${...} PARAM expansion syntax
//          "+[0-9@]" : Array
//                "%" : Remove shortest matching suffix.
//               "%%" : Remove longest matching suffix.
//                "#" : Remove shortest matching prefix.
//               "##" : Remove longest matching prefix.
//          "${#var}" : Length of the variable's value.
// "${var:start:len}" : Substring extraction.
//               ":-" : Default value if unset or null.
//               ":=" : Assign default value if unset or null.
//$(()) ARITHMETIC syntax:
//             "+-*/%" works as expected.
//                "**" exponent.
//              "++--" pre/post increment/decrement.
//              "&|^~" bitwise AND OR XOR NOT respectively 1 character.
//              "<<>>" bitshift left/right.

#ifndef MAXISHELL_H
#define MAXISHELL_H

#ifndef TOKEN_LEN_MAX
# define TOKEN_LEN_MAX 64
#endif

//depth of nested tokens. E.g. `` 
#ifndef TOKEN_NEST_MAX
# define TOKEN_NEST_MAX 64
#endif

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
	LQUOTE,           //"$"", 
	COMMENT,          //"#...\n" interactive_comments enabled as flag.
	KEYWORD,          /*of the following:
	if   then elif   else   fi time
	for  in	  until  while  do done
	case esac coproc select function
	{    }    [[     ]]     !
	*/
	NEGATION,     //"![command|function]"
	PIPE_OUT_ERR, //"|&"
	CMD_AND,      //"&&"
	CMD_OR,       //"||"
	CMD_END,      //";"
	CMD_BG,       //"&" //CMD terminates on ";&\n"
	TILDE_EXPAN,  //"~" is set to $HOME
	SUBSHELL_OLD, //"{"
	SUBSHELL_NEW, //"("
	BRACE_EXPAN,  //"${"
	CMD_SUBST,    //"$(" or "`"
	ARITH_EXPAN,  //"$(("
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

//	static const char	*keywords[27] = {"if", "then", "else", "elif", "fi",
//		"case", "esac", "for", "select", "while", "until", "do", "done",
//		"break", "continue", "function", "return", "local", "time", "in",
//		"export", "readonly", "declare", "let", "shift", "trap", "time", NULL};
typedef struct t_tokenselect
{
	const char	firstchar[128] = {
		['~'] = TILDE, ['!'] = , ['$'] = VARNAME, 
		['<'] = REDIRECT_IN, ['>'] = REDIRECT_OUT, [''] = , 
		//[''] = , [''] = , [''] = , [''] = , [''] = , [''] = , 
	};
	const char	secondchar[128];
} t_tokenselect;

//booleans are mostly for declare builtin.
//bool	is_local; //non-interactive
typedef struct t_env
{
	char	*name;
	void	*value;
	//bool	unset;
	bool	readonly;          //declare -r
	bool	exported;          //declare -x
	bool	integer;           //declare -i
	bool	array;             //declare -a
	bool	associative_array; //declare -A
	bool	reference;         //declare -n
} t_env;

#endif
