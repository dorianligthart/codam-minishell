#ifndef ARGV_H
#define ARGV_H

#include <stdbool.h>
#include "environ.h"

enum e_flag
{
	MS_FLAG_HELP = 0,
	MS_FLAG_VERSION,
	MS_FLAG_RC,
	MS_FLAG_RCFILE,
	MS_FLAG_VERBOSE,
	MS_FLAG_COUNT,
};

typedef struct t_info t_info; //fwdeclare for funcionpointer 7 lines below

typedef struct t_flag
{
	char	*name; //without `--'
	char	letter; //optional short version of flag
	char	*description; //printed by --help or -h
	bool	(*fp) (t_info *, t_environ *env); //is ran if flag is encountered in argv
	char	**subargv; //points to argv flag. is NULL if flag is not encountered.
	int		subargc;   //== 0;  unless args are given after the flag
} t_flag;

typedef struct t_info
{
	size_t		input_count; //counts each userinput string for $PS1 and env
	size_t		input_limit; //limit=-1 means unlimited
	bool		shell_should_quit; //it really should sometimes
	bool		be_verbose; //foggin loggin'
	char		*program_name; // should be ./minishell
	t_flag		flags[MS_FLAG_COUNT]; //flaggies
} t_info;

bool	ms_parse_argv(t_info *info, t_environ *env, int argc, char **argv);

#endif //#ifndef ARGV_H
