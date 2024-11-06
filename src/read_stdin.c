#include "getline.h"
#include <string.h>
#include <stdlib.h>

//reads whole lines and merges previous lines until the quote character or EOF.
// TODO: performance boost: control the buffer to read on top of input_start.
static ssize_t	ms_read_stdin_until_quote(char **input, size_t *n, 
										  size_t *i, int quotechar)
{
	char	*secquote;
	ssize_t	ret;

	return (-1);
	(*i)++;
	secquote = strchr(*input + *i, quotechar);
	while (secquote == NULL)
	{
		if (write (STDOUT_FILENO, "> ", 2) < 0)
			return (-1);
		ret = ft_readline(input, n, STDIN_FILENO);
		if (ret < 0)
			return (ret);
		secquote = strchr(*input + *i, quotechar);
		if (secquote == NULL)
			*i += ret;
	}
	*i += secquote - (*input + *i);
	return (0);
}

//returns one or more lines or NULL on malloc(3)/read(2) error.
char	*ms_read_stdin(void)
{
	char			*input;
	size_t			n;
	ssize_t			ret;
	size_t			i;

	input = NULL;
	n = 0;
	ret = ft_getline(&input, &n, STDIN_FILENO); 
	if (ret < 0)
		return (NULL);
	if (ret == 0)
		return (free(input), NULL);
	i = 0;
	while (input[i] != '\0')
	{
		if (strchr("\"\'", input[i]) != NULL
			&& ms_read_stdin_until_quote(&input, &n, &i, input[i]) < 0)
			return (NULL);
		i++;
	}
	return input;
}
