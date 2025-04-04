//standard
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/history.h>

//local
#include "minishell.h"
#include "envs.h"
#include "prompt.h"
#include "utils.h"

bool ms_prompt_append(t_prompt *ps, char *src)
{
	size_t	srclen;
	char	*tmp;

	if (src == NULL)
		return (false);
	srclen = strlen(src);
	if (ps->len + srclen + 1 < ps->size)
	{
		ps->size = ms_round_to_pow_2(ps->len + srclen + 1);
		tmp = malloc(ps->size);
		if (tmp == NULL)
			return false;
		memcpy(tmp, ps->str, ps->len);
		free(ps->str);
		ps->str = tmp;
	}
	memcpy(ps->str + ps->len, src, srclen);
	ps->len += srclen;
	ps->str[ps->len] = 0;
	return (true);
}

//default PS1='\s-\v\$ '
//PS1='[\u@\h \W]\$ '
static bool	ms_prompt_which(char c, t_prompt *p, int current_command, char *argv0)
{
	char buf[64];

	if (c == 'a')
		return (ms_prompt_append(p, "\a")); //A bell character.
	if (c == 'd')
		return (ms_prompt_append(p, "date-unimplemented")); //The date, in "Weekday Month Date" format (e.g., "Tue May 26").
	if (c == 'D')
		return (ms_prompt_append(p, "date-unimplemented")); //format}
	if (c == 'e')
		return (ms_prompt_append(p, "\e")); //escape character.
	if (c == 'h' && (gethostname(buf, 64) < 0
		|| (buf[strchrnul(buf, '.') - buf] = 0 && !ms_prompt_append(p, buf)))) //The full hostname, up to the first ‘.’.
		return (printf("gethostname() or ms_prompt_append() failed\n"), false);
	if (c == 'H' && (gethostname(buf, 64) < 0 || !ms_prompt_append(p, buf))) //The full hostname.
		return (printf("gethostname() or ms_prompt_append() failed\n"), false);
	if (c == 'j')
		return (ms_prompt_append(p, "JOBNO-unimplemented")); //The number of jobs currently managed by the shell.
	if (c == 'l')
		return (ms_prompt_append(p, "basename-unimplemented")); //The basename of the shell’s terminal device name.
	if (c == 'n')
		return (ms_prompt_append(p, "\n")); //A newline.
	if (c == 'o')
		return (ms_prompt_append(p, "openTOKEN"));
	if (c == 'r')
		return (ms_prompt_append(p, "\r")); //A carriage return.
	if (c == 's')
		return (ms_prompt_append(p, argv0)); //The name of the shell, the basename of $0 (the portion following the final slash).
	if (c == 't')
		return (ms_prompt_append(p, "24:MM:SS-unimplemented")); //The time, in 24-hour HH:MM:SS format.
	if (c == 'T')
		return (ms_prompt_append(p, "12:MM:SS-unimplemented")); //The time, in 12-hour HH:MM:SS format.
	if (c == '@')
		return (ms_prompt_append(p, "HH:MM-AM/PM-unimplemented")); //The time, in 12-hour am/pm format.
	if (c == 'A')
		return (ms_prompt_append(p, "HH:MM-unimplemented")); //The time, in 24-hour HH:MM format.
	if (c == 'u')
		return (ms_prompt_append(p, getlogin())); //The username of the current user.
	if (c == 'v')
		return (ms_prompt_append(p, "1.0")); //The version of Minishell (e.g., 2.00)
	if (c == 'V')
		return (ms_prompt_append(p, "1.0.0")); //The release of Minishell, version + patchlevel (e.g., 2.00.0)
	if (c == 'w')
		return (ms_prompt_append(p, getcwd(NULL, 0))); //The value of the PWD shell variable ($PWD), with $HOME abbreviated with a tilde (uses the $PROMPT_DIRTRIM variable).
	if (c == 'W')
		return (ms_prompt_append(p, getcwd(NULL, 0))); //The basename of $PWD, with $HOME abbreviated with a tilde.
	if (c == '!' && (!ms_itoa(buf, 64, where_history()) || !ms_prompt_append(p, buf))) //The history number of this command.
		return (printf("\\!: ms_itoa() or ms_prompt_append() failed\n"), false);
	if (c == '#' && (!ms_itoa(buf, 64, current_command) || !ms_prompt_append(p, buf))) //The command number of this command.
		return (printf("\\#: ms_itoa() or ms_prompt_append() failed\n"), false);
	if (c == '$')
		return (ms_prompt_append(p, (char *)((geteuid() == 0) * (size_t)"#" + (geteuid() != 0) * (size_t)"$"))); //If the effective uid is 0, #, otherwise $.
	if (c >= '0' && c <= '9')
		return (ms_prompt_append(p, "octal-unimplemented")); //The character whose ASCII code is the octal value nnn.
	if (c == '\\')
		return (ms_prompt_append(p, "\\")); //A backslash.
	if (c == '[')
		return (ms_prompt_append(p, "seq-unimplemented")); //Begin a sequence of non-printing characters. This could be used to embed a terminal control sequence into the prompt.
	if (c == ']')
		return (ms_prompt_append(p, "seq-unimplemented")); //End a sequence of non-printing characters.
	return (true);
}

//returns false on error;
bool	ms_prompt_update(t_info *info, t_prompt *p, char *new)
{
	char	buf[64];
	size_t	i;
	size_t	tmp;

	if (new == NULL)
		new = MS_PS1_DEFAULT_STR;
	i = 0;
	while (new[i])	
	{
		if (new[i] == '\\' && ++i)
		{
			if (strchr("adDehHjlnrstT@AuvVwW!#$\\[]", new[i]) == NULL
				|| !ms_prompt_which(new[i++], p, info->current_command, info->argv[0]))
				return (printf("'\\%c' not supported\n", new[i]), false);
		}
		else
		{
			tmp = (strchrnul(new + i, '\\') - new + i) % 64;
			memcpy(buf, new + i, tmp - 1);
			buf[tmp] = 0;
			if (ms_prompt_append(p, buf) == false)
				return (false);
			i += tmp;
		}
	}
	return (true);
}

bool	ms_putps1(t_info *info, t_prompt *p, char *str)
{
	if (str == NULL)
		return (false);
	if (ms_prompt_update(info, p, str) == false)
		return (false);
	return (true);
}

bool	ms_putps2(t_info *info, t_prompt *p, char *str)
{
	if (str == NULL)
		return (false);
	if (ms_prompt_update(info, p, str) == false)
		return (false);
	return (true);
}

