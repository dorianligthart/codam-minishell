#ifndef MS_ENVIRON_H
# define MS_ENVIRON_H

// todo: make shell support bourne variables. HOME, PATH, IFS, PS1, PS2.
// https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Variables.html
// Will stay unimplemented:
// https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html
enum bash_envs
{
	ENV_CDPATH,
	ENV_HOME,
	ENV_IFS,
	ENV_MAIL,
	ENV_MAILPATH,
	ENV_OPTARG,
	ENV_OPTIND,
	ENV_PATH,
	ENV_PS1,
	ENV_PS2,
	ENV_BOURNE_COUNT,
	ENV__,
	ENV_BASH,
	ENV_BASHOPTS,
	ENV_BASHPID,
	ENV_BASH_ALIASES,
	ENV_BASH_ARGC,
	ENV_BASH_ARGV,
	ENV_BASH_ARGV0,
	ENV_BASH_CMDS,
	ENV_BASH_COMMAND,
	ENV_BASH_COMPAT,
	ENV_BASH_ENV,
	ENV_BASH_EXECUTION_STRING,
	ENV_BASH_LINENO,
	ENV_BASH_LOADABLES_PATH,
	ENV_BASH_REMATCH,
	ENV_BASH_SOURCE,
	ENV_BASH_SUBSHELL,
	ENV_BASH_VERSINFO,
	ENV_BASH_VERSION,
	ENV_BASH_XTRACEFD,
	ENV_CHILD_MAX,
	ENV_COLUMNS,
	ENV_COMP_CWORD,
	ENV_COMP_LINE,
	ENV_COMP_POINT,
	ENV_COMP_TYPE,
	ENV_COMP_KEY,
	ENV_COMP_WORDBREAKS,
	ENV_COMP_WORD,
	ENV_COMPREPLY,
	ENV_COPROC,
	ENV_DIRSTACK,
	ENV_EMACS,
	ENV_ENV,
	ENV_EPOCHREALTIME,
	ENV_EPOCHSECONDS,
	ENV_EUID,
	ENV_EXECIGNORE,
	ENV_FCEDIT,
	ENV_FIGNORE,
	ENV_FUNCNEST,
	ENV_GLOBIGNORE,
	ENV_GROUPS,
	ENV_histchars,
	ENV_HISTCMD,
	ENV_HISTCONTROL,
	ENV_HISTFILE,
	ENV_HISTFILESIZE,
	ENV_HISTIGNORE,
	ENV_HISTSIZE,
	ENV_HISTTIMEFORMAT,
	ENV_HOSTFILE,
	ENV_HOSTNAME,
	ENV_HOSTTYPE,
	ENV_IGNOREEOF,
	ENV_INPUTRC,
	ENV_INSIDE_EMACS,
	ENV_LANG,
	ENV_LC_ALL,
	ENV_LC_COLLATE,
	ENV_LC_CTYPE,
	ENV_LC_MESSAGES,
	ENV_LC_NUMERIC,
	ENV_LC_TIME,
	ENV_LINENO,
	ENV_LINES,
	ENV_MACHTYPE,
	ENV_MAILCHECK,
	ENV_MAPFILE,
	ENV_OLDPWD,
	ENV_OPTERR,
	ENV_OSTYPE,
	ENV_PIPESTATUS,
	ENV_POSIXLY_CORRECT,
	ENV_PPID,
	ENV_PROMPT_COMMAND,
	ENV_PROMPT_DIRTRIM,
	ENV_PS0,
	ENV_PS3,
	ENV_PS4,
	ENV_PWD,
	ENV_RANDOM,
	ENV_READLINE_ARGUMENT,
	ENV_READLINE_LINE,
	ENV_READLINE_MARK,
	ENV_READLINE_POINT,
	ENV_REPLY,
	ENV_SECONDS,
	ENV_SHELL,
	ENV_SHELLOPTS,
	ENV_SHLVL,
	ENV_SRANDOM,
	ENV_TIMEFORMAT,
	ENV_TMOUT,
	ENV_TMPDIR,
	ENV_UID,
	ENV_COUNT, //last
};

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h> 

//OVERVIEW:
// local variables | exported variables
// - bashrc envs   | - past variables from <stdio.h>(char **environ)
// - user def vars | 	- sh exported vars
// - sh envs       | - user exported vars

//STRUCT DEF:
//ptr:    grows linearly. if an env gets unset the pointer will be filled with an
//        empty string, and marked for availability
//table1: are indexes to first hits of hash algo.
//table2: are indexes to second hits of hash algo.
//table3: are indexes to third hits of hash algo.
//          when 4th time hit, the size of table will double.
typedef struct t_environ
{
	size_t		size;
	char		**ptr;
	bool		*ismalloced;
	bool		*islocal;
	uint32_t	*table1;
	uint32_t	*table2;
	uint32_t	*table3;
	uint32_t	seed;
	size_t		tablesize;
} t_environ;

#ifndef MS_ENVSIZE
#define MS_ENVSIZE 64
#endif

bool	ms_envrealloc(t_environ *env, size_t newsize);
char	*ms_getenv(char *str, t_environ *env);
bool	ms_setenv(char *str, t_environ *env, bool islocal);
void	ms_unsetenv(char *str, t_environ *env);

#endif //#ifndef MS_ENVIRON_H

//OLD DATA STRUCT:
////at start: NULL.
////if ms_setenv(local): reallocate.
//	uint32_t	local_size;
//	char		**local;
//	bool		*local_is_malloced;
////at start: set to environ.
////if ms_setenv(export): reallocate.
//	uint32_t	export_size;
//	char		**export;
//	bool		*export_is_malloced;
////at start: always alloced and gen table.
////if ms_setenv() AND hashptr2 is full: regen.
