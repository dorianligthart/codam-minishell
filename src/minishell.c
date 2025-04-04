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

//TODO: do this in seperate process so user can type from start of program.
//unlike bash ugh and wait for input at lexer.
static inline bool	ms_initialise(t_shell *sh)
{
	const char	*str = "";

	sh->info.empty_string = str;
	if (ms_env_init(&sh->exp_env, true) == false 
		|| ms_lexer_init(&sh->lexer) == false
		|| ms_parser_init(&sh->parser) == false)
		return (false);
	return (true);
}

//expects a proper t_shell struct.
bool	ms_exec(t_shell *sh)
{
	if (ms_lexer_go(&sh->lexer, sh->cmdstr) == false
		|| ms_parser_go(&sh->parser, &sh->lexer) == false)
		return (false);
	add_history(sh->cmdstr);
	if (ms_exec_go(sh) == false)
		return (false);
	return (true);
}

//challenges:
// echo hello && ((echo hi; echo) < test.txt)
// ((echo hi; cat) < test.txt) > cat
// ((echo hi; cat) < test.txt) ; cat
//Big differences!

//signal(SIGQUIT, ms_exit);
    //signal(SIGINT, ms_exit);
	//if (EOF CTRL+d) ms_exit();
int	main(int argc, char *argv[])
{
	t_shell		sh;
	int			ret;
	char		*prompt;

	bzero(&sh, sizeof(t_shell));
	sh.info.argc = argc;
 	sh.info.argv = argv;
	if (ms_initialise(&sh) == false)
		return (ms_free(&sh), EXIT_FAILURE);
	while (true)
	{
		prompt = ms_getenv("PS1", &sh.loc_env, &sh.exp_env);
		if (prompt == NULL)
			ms_setenv(&sh.loc_env, "PS1", MS_PS1_DEFAULT_STR);
ms_free(&sh);
return (0);
		if (write(STDOUT_FILENO, sh.ps1.str, strlen(sh.ps1.str)) < 0)
			return (ms_free(&sh), EXIT_FAILURE);
		ret = ft_getline(&sh.cmdstr, &sh.cmdsize, STDIN_FILENO);
		if (ret == 0)
			return (printf("\nexit\n"), ms_free(&sh), EXIT_SUCCESS);
		if (ret < 0 || ms_exec(&sh) == false)
			return (ms_free(&sh), EXIT_FAILURE);
	}
	ms_free(&sh);
	return (EXIT_SUCCESS);
}

