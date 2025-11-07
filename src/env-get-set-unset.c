#include "environ.h"
#include "utils.h"
#include "hash.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//regen hashes yayyyy
bool	ms_expandenv(t_environ *e, size_t newsize)
{
	t_variable	*new;

	new = malloc(newsize * sizeof(t_variable));
	if (new == NULL)
		return (false);
	memset((char *)new, '\0', newsize * sizeof(t_variable));
	memcpy(new, e->vars, newsize * sizeof(t_variable)); //TODO: hash...
	return (true);
}

t_variable	*ms_getenv(char *str, t_environ *e)
{
	t_variable	*var;
	size_t		len;

	len = ms_strchrlen(str, '=');
	var = e->vars + ms_hash(str, len, e->seed) % e->size;
	while (var->next && strncmp(str, *(var->str), len))
		var = var->next;
	if (strncmp(str, *(var->str), len) == 0)
		return (var);
	return (NULL);
}

void	ms_unsetenv(char *id, t_environ *e)
{
	
}

bool	ms_setenv(char *id, char *value, t_environ *e, bool islocal)
{
	const size_t	valuelen = strlen(value);
	size_t			idlen;
	t_variable		*var;

	var = ms_getenv(id, e);
	if (var == NULL) //new env
	{
		var = e->vars + e->lowest_free;
		while (e->vars[++(e->lowest_free)].str != NULL)
			if (e->lowest_free == e->size && !ms_expandenv(e, e->size * 2))
				return (printf("Error: Expanding environment "
				               "variables array malloc() failed.\n"), false);
	}
	idlen = ms_strchrlen(id, '=');
	var->str = malloc(idlen + valuelen + 1);
	if (var->str == NULL)
		return (false);
	var->str[idlen + valuelen] = 0;
	memcpy(var->str, id, idlen);
	memcpy(var->str + idlen, value, valuelen);
	return (true);
}

//islocal = whether variable is exported. see man export(1) and bash for more info.
bool	ms_setenv_ptr(char **var, size_t *varsize, t_environ *e, bool islocal)
{
	t_variable	*new;

	if (var == NULL || *var == NULL)
		return (printf("Error: ms_setenv() got NULL pointer.\n"), false);
	new = ms_getenv(*var, e);
	if (new == NULL) //is new env
	{
		new = e->vars + e->lowest_free;
		while (e->vars[++(e->lowest_free)].str != NULL)
			if (e->lowest_free == e->size && !ms_expandenv(e, e->size * 2))
				return (printf("Error: Expanding environment "
				               "variables array malloc() failed.\n"), false);
	}
	if (new->strsize && *new->strsize > 0)
	{
		free(*new->str);
		new->strsize = varsize;
	}
	new->str     = var;
	new->islocal = islocal;
	return (true);
}

