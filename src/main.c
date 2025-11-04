//unix:
#include <unistd.h>
//libc:
#include <stdbool.h> //true false bool
#include <stdlib.h> //malloc() free()
#include <string.h> //memset()
#include <stdio.h> //somehow needed for history.h
//readline:
#include <readline/history.h> //add_history()

//local:
#include "minishell.h" //t_shell, enum
#include "argv.h" //enum
#include "environ.h" //ms_environ_init()
#include "prompt.h" //ms_prompt_init()
#include "getline.h" //ft_getline()
#include "lexer.h" //ms_lexer_init()
#include "parser.h" //ms_parser_init()
#include "exec.h" //ms_exec_init()
#include "utils.h" //ms_free()

static void	ms_free(t_shell *sh)
{
	if (sh->ps1.size != 0)
		free(sh->ps1.str);
	if (sh->ps2.size != 0)
		free(sh->ps2.str);
	if (sh->cmdsize != 0)
		free(sh->cmdstr);
	if (sh->lexer.size != 0)
		free(sh->lexer.tokens);
}

int	ms_getinput(t_shell *sh)
{
	//if (ms_prompt_update(&sh.info, &sh.ps1, ms_getenv_str("PS1", &sh.env)) == false)
	//	return (ms_free(&sh), EXIT_FAILURE);
	if (write(STDOUT_FILENO, sh->ps1.str, sh->ps1.len) < 0)
		return (ms_free(sh), EXIT_FAILURE);
	return (ft_getline(&sh->cmdstr, &sh->cmdsize, STDIN));
}

int	main(int argc, char *argv[])
{
	t_shell		sh;
	int			ret;

	bzero(&sh, sizeof(t_shell));
	sh.info.input_limit = (uint32_t)-1; //unlimited
	if (!ms_initenv(&sh.envs)
		|| !ms_parse_argv(&sh.info, &sh.envs, argc, argv)
		|| !ms_initlexer(&sh.lexer)
		|| !ms_initparser(&sh.parser)
		|| !ms_initexec(&sh))
		return (EXIT_FAILURE);
	sh.ps1.str = "Minishell> "; //TODO: replace this with variadic PS1 env string
	sh.ps1.len = strlen(sh.ps1.str);
	while (sh.info.shell_should_quit == false
		&& (sh.info.input_limit == (uint32_t)-1 || sh.info.input_count++ < sh.info.input_limit))
	{
		ret = ms_getinput(&sh);
		if (ret == 0)
			break;
		if (ret < 0
			|| ms_lexer(&sh.lexer, sh.cmdstr) == false
			|| ms_parse(&sh.parser, &sh.lexer) == false
			|| ms_exec(&sh.parser, &sh.info) == false)
			return (ms_free(&sh), EXIT_FAILURE);
		add_history(sh.cmdstr);
	}
	printf("Goodbye!\n");
	ms_free(&sh);
	return (EXIT_SUCCESS);
}
//		for (size_t i = 0; i < sh.lexer.count; ++i)
//			printf("[INFO] token='%.*s'\n",
//				(int)(sh.lexer.tokens[i].end - sh.lexer.tokens[i].begin),
//				sh.cmdstr + sh.lexer.tokens[i].begin);

//difficult problems:
// echo hello && ((echo hi; echo) < test.txt)
// ((echo hi; cat) < test.txt) > cat
// ((echo hi; cat) < test.txt) ; cat
// Signals:
//	signal(SIGQUIT, ms_exit);
//	signal(SIGINT, ms_exit);
//	if (EOF CTRL+d) ms_exit();
