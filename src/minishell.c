//standard:
#include <unistd.h>
#include <stdbool.h> //true false bool
#include <stdlib.h> //malloc() free() strdup()
#include <string.h> //memset()

//TODO: rm and check potential bug. Mail: bug-readline@gnu.org:
// readline/rltypedefs.h:71 typedef int rl_getc_func_t (FILE *);
// Error: FILE is used but stdio.h not included
#include <stdio.h>
#include <readline/history.h> //add_history()

//local:
#include "minishell.h" //t_shell, enum
#include "envs.h" //ms_environ_init()
#include "prompt.h" //ms_prompt_init()
#include "lexer.h" //ms_lexer_init(), TOKEN enum
#include "parser.h" //ms_parser_init()
#include "exec.h" //ms_exec_init()
#include "getline.h" //ft_getline()
#include "utils.h" //ms_free()

//main2() because 25 line rule :)))))
bool	main2(t_shell *sh)
{
	if (ms_lex(&sh->lexer, sh->cmdstr) == false
		|| ms_parse(&sh->parser, &sh->lexer) == false)
		return (false);
	add_history(sh->cmdstr);
	if (ms_exec(sh) == false)
		return (false);
	return (true);
}

static inline bool	ms_initshell(t_shell *sh)
{
	if (ms_envrealloc(&sh->env, MS_ENVSIZE) == false
		|| ms_setenv("PS1=> ", &sh->env, false) == false
		|| ms_setenv(MS_PS2_DEFAULT_STR, &sh->env, false) == false
		|| ms_initlexer(&sh->lexer) == false
		|| ms_initlexer(&sh->lexer) == false
		|| ms_initexec(sh) == false)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_shell		sh;
	int			ret;
	const char	str[1] = {0};

	bzero(&sh, sizeof(t_shell));
	sh.info.empty_string = str;
	sh.info.argc = argc;
 	sh.info.argv = argv;
	if (ms_initshell(&sh) == false)
		return (ms_free(&sh), EXIT_FAILURE);
	while (true)
	{
		if (ms_prompt_update(&sh.info, &sh.ps1, ms_getenv("PS1", &sh.env)) == false)
			return (ms_free(&sh), EXIT_FAILURE);
		if (write(STDOUT_FILENO, sh.ps1.str, strlen(sh.ps1.str)) < 0)
			return (ms_free(&sh), EXIT_FAILURE);
		ret = ft_getline(&sh.cmdstr, &sh.cmdsize, STDIN_FILENO);
		if (ret == 0)
			return (printf("\nGoodbye!\n"), ms_free(&sh), EXIT_SUCCESS);
		if (ret < 0 || main2(&sh) == false)
			return (ms_free(&sh), EXIT_FAILURE);
	}
	ms_free(&sh);
	return (EXIT_SUCCESS);
}

//challenges:
// echo hello && ((echo hi; echo) < test.txt)
// ((echo hi; cat) < test.txt) > cat
// ((echo hi; cat) < test.txt) ; cat
// Signals:
//	signal(SIGQUIT, ms_exit);
//	signal(SIGINT, ms_exit);
//	if (EOF CTRL+d) ms_exit();
