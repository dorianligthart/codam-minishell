//definitions of getline.h
//ft_getline_split(), ft_getline_read(), located in getline_utils.c

#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include "getline.h"

ssize_t ft_getdelim(char **lineptr, size_t *n, int delim, int fd)
{
	static char		*saved[512] = {0};
	ssize_t			readret;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (saved[fd] != NULL && strchr(saved[fd], delim))
		return ( ft_getline_split(lineptr, &saved[fd], delim) );
	while (saved[fd] == NULL || !strchr(saved[fd], delim))
	{
		readret = ft_getline_read(n, fd, saved);
		if (readret < 0)
			return (free(saved[fd]), -1);
		if (readret == 0)
			return (*lineptr = saved[fd], saved[fd] = NULL, strlen(*lineptr));
	}
	return ( ft_getline_split(lineptr, &saved[fd], delim));
}

ssize_t	ft_readdelim(char **lineptr, size_t *n, int delim, int fd)
{
	static char		*saved[1024] = {0};
	ssize_t			readret;
	ssize_t			nread;

	if (lineptr == NULL || n == NULL)
		return (-1);
	nread = 0;
	while (saved[fd] == NULL || !strchr(saved[fd], delim))
	{
		readret = ft_getline_read(n, fd, saved);
		if (readret < 0)
			return (free(saved[fd]), -1);
		nread += readret;
		if (readret == 0)
			return (*lineptr = saved[fd], saved[fd] = NULL, strlen(*lineptr));
	}
	return ( ft_getline_split(lineptr, &saved[fd], delim), nread);
	
}

ssize_t	ft_getline(char **lineptr, size_t *n, int fd)
{
	return (ft_getdelim(lineptr, n, '\n', fd));
}

ssize_t	ft_readline(char **lineptr, size_t *n, int fd)
{
	return (ft_readdelim(lineptr, n, '\n', fd));
}

char	*get_next_line(int fd)
{
	char	*line;
	size_t	n;

	line = NULL;
	ft_getline(&line, &n, fd);
	return (line);
}

//int main(void)
//{
//	char	*line = NULL;
//	size_t	n = 0;
////	getline(&line, &n, stdin);
////	printf("main() retrieved: %s", line);
////	free(line);
////	return 0;
//
//	ssize_t	readreturn = 1;
//	while (readreturn > 0)
//	{
//		readreturn = ft_getline(&line, &n, 0);
//		if (readreturn < 0)
//			break ;
//		printf("main() retrieved: %s", line);
//	}
//	free(line);
//	return (0);
//}
