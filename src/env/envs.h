//'src/envs/envs.c' is associated with this header.
#ifndef MS_ENVIRON_H
# define MS_ENVIRON_H

// TODO: make shell support bourne variables. HOME, PATH, IFS, PS1, PS2.
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
// two t_environ's for:
// local variables | exported variables
// - bash envs     | - copy extern char **environ variables from <stdio.h>
// - user def vars | - user exported vars
// - bourne envs   | - bourne envs 

//STRUCT DEF:
//ptr:      grows linearly. if an env gets unset the pointer will be filled with an
//          empty string, and marked for availability
//hashptr:  are indexes to first hits of hash algo.
//hashptr2: are indexes to second hits of hash algo.
//hash:     when 3rd time hit, the size of table will double.
typedef struct t_environ
{
	uint32_t	ptrsize;
	char		**ptr;
	bool		*ismalloced;

	uint32_t	*hashptr;
	uint32_t	*hashptr2;
	size_t		hashsize;
} t_environ;

#ifndef MS_ENVSIZE
#define MS_ENVSIZE 64
#endif

char	*ms_getenv(char *id, t_environ *loc, t_environ *exp);
bool	ms_setenv_str(t_environ *env, char *str);
bool	ms_setenv(t_environ *env, char *id, char *val);
bool	ms_unsetenv(t_environ *env, char *id);
bool	ms_env_realloc(t_environ *env, size_t newcount);
bool	ms_env_init(t_environ *env, bool copyenviron);

#endif //#ifndef MS_ENVIRON_H
