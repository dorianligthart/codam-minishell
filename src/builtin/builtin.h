#ifndef BUILTIN_H
# define BUILTIN_H

enum e_builtin
{
	BUILTIN_CD,
	BUILTIN_ENV,
	BUILTIN_PWD,
	BUILTIN_ECHO,
	BUILTIN_EXIT,
	BUILTIN_UNSET,
	BUILTIN_EXPORT,
	BUILTIN_COUNT
};

#include "minishell.h" //t_ms_state

int	builtin_cd(t_ms_state *s, int argc, char **argv, char **envp);
int	builtin_env(t_ms_state *s, int argc, char **argv, char **envp);
int	builtin_pwd(t_ms_state *s, int argc, char **argv, char **envp);
int	builtin_echo(t_ms_state *s, int argc, char **argv, char **envp);
int	builtin_exit(t_ms_state *s, int argc, char **argv, char **envp);
int	builtin_unset(t_ms_state *s, int argc, char **argv, char **envp);
int	builtin_export(t_ms_state *s, int argc, char **argv, char **envp);

#endif //#ifndef BUILTIN_H
