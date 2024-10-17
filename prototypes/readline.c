#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

char    *get_line()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline("minishell$ ");
    if (line)
        add_history(line);
    return (line);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT || signum == SIGTERM)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int main(void)
{
    char    *line;

	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
    while (1)
	{
		line = get_line();
		if (*line)
			printf("%s\n", line);
	}
	return (0);
}

