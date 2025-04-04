	//extension of getline.c
	//defined in getline.h

#include <sys/types.h>
#include <stddef.h>
#include "getline.h"

ssize_t	ft_getline(char **lineptr, size_t *n, int fd)
{
	return (ft_getdelim(lineptr, n, '\n', fd));
}

ssize_t	ft_readline(char **lineptr, size_t *n, int fd)
{
	return (ft_readdelim(lineptr, n, '\n', fd));
}

char	*ft_get_next_line(int fd)
{
	char	*line;
	size_t	n;

	line = NULL;
	n = 0;
	if (ft_getdelim(&line, &n, '\n', fd) < 0)
		return (NULL);
	return (line);
}

