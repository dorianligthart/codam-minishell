#include "argv.h"
#include "environ.h"
#include "utils.h" //ms_strchrlen()
#include <string.h>
#include <stdio.h>
#include <ctype.h>

bool	ms_flag_rcfile(t_info *info, t_environ *env)
{
	return (true);
}

//via argv easier than an rc-file?
bool	ms_flag_rc(t_info *info, t_environ *env)
{
	return (true);
}

bool	ms_flag_verbose(t_info *info, t_environ *env)
{
	info->be_verbose = true;
	return (true);
}

bool	ms_flag_help(t_info *info, t_environ *env)
{
	size_t		i;
	t_variable	*var;

	info->shell_should_quit = true;
	printf("Dorians minishell, version 1.0.0\n");
	printf("options: \n");
	i = -1;
	while (++i < MS_FLAG_COUNT)
	{
		printf("  --%s -%c\n", info->flags[i].name, info->flags[i].letter);
		printf("  %s\n",       info->flags[i].description);
	}
	var = ms_getenv("HOME", env);
	printf("rc-file path: %s/.bashrc\n", *var->str);
	printf("source: https://github.com/dorianligthart/codam-minishell\n");
	return (true);
}

bool	ms_flag_version(t_info *info, t_environ *env)
{
	info->shell_should_quit = true;
	printf("42's Minishell v1.0.0\n");
	printf("But it got kind of big haha\n");
	(void)env;
	return (true);
}

	//TODO: instead of looping maybe hash? probably overkill:
	//heap/stack overhead, not many options, they have few characters, and we're here only once.
static bool	ms_parse_a_flag(t_info *info, t_environ *env, char **argv, int *i)
{
	size_t	len;
	int		current;
	char 	*name;

	name = argv[*i] + 1 + (argv[*i][1] == '-');
	len = 0;
	while (isprint(name[len]) && name[len] != '=' &&
		  !isspace(name[len]) && !strchr(MS_METACHARS, name[len]))
		len++;
	if (len == 0)
		return (printf("Error: don't know what you mean with: '%s'\n", argv[*i]), false);
	current = 0; 
	while (current < MS_FLAG_COUNT)
	{
		if (len == 1 && info->flags[current].letter == name[0]) //letter match
			info->flags[current].subargv = argv + *i;
		else if (!strncmp(name, info->flags[current].name, len)) //name match
			info->flags[current].subargv = argv + *i;
		if (info->flags[current].subargv != NULL) //matched?
		{
			while (argv[++(*i)] && argv[*i][0] != '-')
				info->flags[current].subargc++;
			return (info->flags[current].fp(info, env));
		}
		current++;
	}
	return (printf("Error: invalid flag '%s'.\n", argv[*i]), false);
}

static bool	ms_parse_flags(t_info *info, t_environ *env, int argc, char **argv)
{
	int		i;

	i = 0;
	while (i != argc && info->shell_should_quit == false)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-' && !isprint(argv[i][2]))
			break; //end of flags
		if (argv[i][0] != '-' && (!isprint(argv[i][1]) || argv[i][0] != '-') && ++i)
			continue; //between program_name and the first flag.
		if (ms_parse_a_flag(info, env, argv, &i) == false)
			return (false);
	}
#if 0
	printf("argv = [\n");
	for (int i = 0; i < argc; ++i) printf("\t[%i]='%s',\n", i, argv[i]);
	printf("]\n");
	printf("flags = [\n");
	for (int i = 0; i < MS_FLAG_COUNT; ++i)
		if (info->flags[i].subargv)
			printf("\t[%i]='%s' with %i arguments,\n", i, info->flags[i].subargv[0], info->flags[i].subargc);
	printf("]\n");
#endif
	return (true);
}

//debug:
#include <assert.h>
//printf("%zu: [names=%zu, letters=%zu, descriptions=%zu, fp=%zu\n", MS_FLAG_COUNT, sizeof(names)/sizeof(*names), sizeof(letters)/sizeof(*letters), sizeof(descriptions)/sizeof(*descriptions), sizeof(fp)/sizeof(*fp));

//TODO: names and letters can be NULL and 0 if prefered, they won't be matched.
//maybe move this to main.c and directly set values in t_info; 25 line rule tho.
//TODO: get rid of assert()
bool	ms_parse_argv(t_info *info, t_environ *env, int argc, char **argv)
{
	char	*names[] = {"help", "version", "readcommand", "rcfile", "verbose",};
	char	letters[] = {'h', 'v', 'c', 'r', 'V',};
	char	*descriptions[] = {"prints this help message then exits.",
			   "prints the version number then exits.",
			   "run commands at startup.",
			   "run commands at startup from a file.",
			   "will make the shell verbose in what it does."};
	bool	(*fp[]) (t_info *, t_environ *) = {ms_flag_help, ms_flag_version,
				ms_flag_rc, ms_flag_rcfile, ms_flag_verbose};
	assert(    sizeof(names)        / sizeof(*names)        == MS_FLAG_COUNT
			&& sizeof(letters)      / sizeof(*letters)      == MS_FLAG_COUNT
	    	&& sizeof(descriptions) / sizeof(*descriptions) == MS_FLAG_COUNT
			&& sizeof(fp)           / sizeof(*fp)           == MS_FLAG_COUNT);

	size_t	i = -1;
	while (++i < MS_FLAG_COUNT)
	{
		if (names[i] && strlen(names[i]) == 1)
			return (printf("Error: %s:%i '--%s' cant be a single character.\n",
							__FILE__, __LINE__, names[i]), false);
		info->flags[i].name        = names[i];
		info->flags[i].letter      = letters[i];
		info->flags[i].description = descriptions[i];
		info->flags[i].fp          = fp[i];
	}
	info->program_name = argv[0]++;
	return (ms_parse_flags(info, env, argc, argv));
}
