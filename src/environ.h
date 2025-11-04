#ifndef ENVIRON_H
# define ENVIRON_H

// https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Variables.html
// Bourne shell vars are implemented.
//
// https://www.gnu.org/software/bash/manual/html_node/Bash-Variables.html
// Will stay unimplemented because what the actual fuck, there are too many and
// some are garbage.
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

//OVERVIEW:
// local variables | exported variables
// - bashrc envs   | - past variables from <stdio.h>(char **environ)
// - user def vars | - exported shell vars passed via argv or .rcfile
// - shell envs    | - current 'exported' vars

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h> 

//start size of (or multiplicate of) env->envp.
#ifndef MS_ENVSIZE
#define MS_ENVSIZE 64
#endif

#ifndef MS_HASH_THRESHOLD
#define MS_HASH_THRESHOLD 6
#endif

//attributes seperate from envp because child processes.
typedef struct t_variable
{
	char		**str;
	size_t		*strsize;
	bool		islocal;
	struct t_variable *next; //possible duplicate hit by hash
} t_variable;

typedef struct t_environ
{
	uint32_t	size;
	char		**envp;	//is prepared to pass to execve(). NULL terminated.
	t_variable	*vars; //2 times as big as ARRAY_LEN(envp).
	uint32_t	seed; //after duplicate hit of MS_HASH_THRESHOLD
	uint32_t	lowest_free; //index to the first free char * in envp.
							 //NOTE: eq to `size` if there are none available.
} t_environ;

//	src/environ.c
//bool	ms_setenv_bourne(t_environ *env);
bool	ms_initenv(t_environ *env);

//	src/env-get-set-unset.c:
t_variable	*ms_getenv(char *id, t_environ *e);
char		*ms_getenv_str(char *id, t_environ *e);
bool		ms_setenv(char **ptr, size_t *ptrsize, t_environ *e, bool islocal);
bool		ms_setallocedenv(char **var, size_t *varsize, t_environ *e, bool islocal);

#endif //#ifndef ENVIRON_H
