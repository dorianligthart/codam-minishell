#include "minishell.h"

int	builtin_env(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	return (1);
}

int	builtin_unset(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	return (1);
}

int	builtin_export(t_shell *sh, int argc, char **argv, char **envp)
{
	(void)sh;
	(void)argc;
	(void)argv;
	(void)envp;
	return (1);
}
