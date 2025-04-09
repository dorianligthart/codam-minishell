#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct t_substr
{
	char	*begin;
	char	*end;
} t_substr;

//current = iterator.
//count = length of buffer of items.
typedef struct t_mult_substr
{
	t_substr	*items;
	size_t		current;
	size_t		count;
} t_mult_substr;

char	*strchr_or_eos(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c) i++;
	return ((char *)str + i);
}

size_t	ms_set_substr_struct(t_substr *dst, char *src, char c)
{
	size_t ui = 0;
	while (*src)
	{
		while (*src == c) src++;
		if (dst != NULL)
		{
			dst[ui].begin = src;
			dst[ui].end = strchr_or_eos(src, c);
		}
		src = strchr_or_eos(src, c);
		ui++;
		while (*src == c) src++;
	}
	return (ui);
}

//debug:
void	ms_print_substrings(t_mult_substr paths, char *begin, char *seperator, char *end)
{
	size_t	i;

	if (begin == NULL || seperator == NULL || end == NULL) return ;
	write(STDOUT_FILENO, begin, strlen(begin));
	i = -1;
	while (++i < paths.count)
	{
		int length = paths.items[i].end - paths.items[i].begin;
		if (length > 0)
			printf("%.*s", length, (char *)paths.items[i].begin);
		else
			printf("null");
		if (i + 1 < paths.count)
			printf("%s", seperator);
	}
	fflush(stdout);
	write(STDOUT_FILENO, end, strlen(end));
}

//minishell specific:
#include <string.h>

char	**ms_get_cmd_strings(t_mult_substr *src, char *suffix)
{
	char		**dst;
	t_substr	cur;
	int			iter;
	int			len;

	dst = (char **)malloc(src->count * sizeof(char *));
	if (dst == NULL)
		return (NULL);
	iter = 0;
	while (iter < src->count)
	{
		cur = src->items[iter];
		len = snprintf(NULL, 0, "%.*s/%s", (cur.end - cur.begin) + 1, cur.begin, suffix); 
		if (len == -1)
			return NULL;
		dst[iter] = malloc(len + 1);
		if (dst[iter] == NULL)
		{
			while (iter--)
				free(dst[iter]);
			return (NULL);
		}
		dst[iter][len] = 0;
		sprintf(dst[iter], "%.*s/%s", cur.end - cur.begin, cur.begin, suffix); 
		iter++;
	}
	return (dst);
}

//env format looks like: name=value1:value2:value3
//where : is delim.
//:: becomes :
//trailing :'s are ignored
int main (int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <cmd>", argv[0]);
		return (1);
	}
	char			*tmp;
	size_t			current;
	t_mult_substr	paths;
	char *env = getenv("PATH");
	//char *env = "/hello/::./world:/bin:/usr/bin:";
	
	memset(&paths, 0, sizeof(t_mult_substr));
	if (env == NULL || *env == 0)
		return (printf("getenv() returned NULL or points to 0\n"), EXIT_FAILURE);

	paths.count = ms_set_substr_struct(NULL, env, ':');
	paths.items = malloc(paths.count * sizeof(t_substr));
	if (paths.items == NULL)
		return (printf("Buy more ram! (paths.items)\n"), EXIT_FAILURE);
	ms_set_substr_struct(paths.items, env, ':');
	printf("env: '%s'\n", env);
	//printf("len: %zu\ncount: %zu\n", strlen(env), paths.count);
	fflush(stdout);

	ms_print_substrings(paths, "converted to: [", ", ", "]\n");

	char **result = ms_get_cmd_strings(&paths, argv[1]);
	if (result == NULL) {
		free(paths.items);
		return (printf("Buy more ram! (result)\n"), EXIT_FAILURE);
	}
	printf("STRINGS MADE: [\n");
	for (size_t i = 0; i < paths.count; ++i) printf("\t'%s',\n", result[i]);
	printf("]\n");
	while (paths.count--)
		free(result[paths.count]);
	free(paths.items);
	free(result);
	return EXIT_SUCCESS;
}

