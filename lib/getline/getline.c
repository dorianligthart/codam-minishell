//definitions of getline.h
//util functions located in getline_utils.c

#include <stdlib.h>     //malloc() free()
#include <unistd.h>     //read()
#include <string.h>     //memcpy(), strlen()

/* GL_EOF  is '(void *)-1' which is a hacky way to let the next call
           of getdelim() or readdelim() know EOF has been reached on that fd.
GL_BUFSIZE all buffer sizes used in this program are either a
           multiplication or duplication of GL_BUFSIZE.
           and has to be bigger than 1.
FD_SETSIZE is the maximum number of open file descriptors per program,
           starting from 4 to FD_SETSIZE.
           If not, this libraries functions will return -1.    */
#define GL_EOF (void *)-1
#ifndef GL_BUFSIZE
# define GL_BUFSIZE 256
#endif
#include <sys/select.h> //definition of FD_SETSIZE

//Tries to append-read from filedescriptor fd to *lineptr.
//returns: read(2) return-value or -1 in case of malloc(3) error.
static ssize_t	gl_read(char **lineptr, size_t *bufsize, size_t index, int fd)
{
	ssize_t	readret;
	char	*realloc;

	if (*lineptr == NULL || *bufsize <= index + GL_BUFSIZE)
	{
		*bufsize = (index / GL_BUFSIZE + 1) * GL_BUFSIZE;
		realloc = malloc(*bufsize);
		if (realloc == NULL)
			return (-1);
		memcpy(realloc, *lineptr, *bufsize);
		*bufsize *= 2;
		free(*lineptr);
		*lineptr = realloc;
	}
	readret = read(fd, *lineptr + index, GL_BUFSIZE - 1);
	if (readret >= 0)
		(*lineptr)[index + readret] = '\0';
	return (readret);
}

//alligns memory block with GL_BUFSIZE
static ssize_t	gl_cpy(char **dst, size_t *bufsize, size_t index, char *src)
{
	size_t	len;
	
	len = 0;
	if (src != NULL)
		len = strlen(src);
	if ((*dst == NULL || *bufsize <= index + len))
	{
		if (*dst != NULL)
			free(*dst);
		*bufsize = ((index + len) / GL_BUFSIZE + 1) * GL_BUFSIZE;
		*dst = malloc(*bufsize);
		if (*dst == NULL)
			return (-1);
	}
	memcpy(*dst + index, src, len);
		(*dst)[index + len] = '\0';
	return (len);
}

// returns the amount of bytes read until delim was found, or -1 on error.
ssize_t ft_getdelim(char **lineptr, size_t *bufsize, int delim, int fd)
{
	static char		*saved[FD_SETSIZE] = {0};
	static size_t	sizes[FD_SETSIZE] = {0};
	ssize_t			readret;
	size_t			i;

	if (lineptr == NULL || bufsize == NULL || fd < 0
		|| GL_BUFSIZE < 2 || FD_SETSIZE < 3 || saved[fd] == GL_EOF)
		return (-1);
	i = 0;
	if (gl_cpy(lineptr, bufsize, i, saved[fd]) < 0)
		return (-1);
	readret = 0;
	while (strchr(*lineptr + i, delim) == NULL)
	{
		i += readret;
		readret = gl_read(lineptr, bufsize, i, fd);
		if (readret < 0)
			return (-1);
		if (readret == 0)
			return (saved[fd] = GL_EOF, strlen(*lineptr));
	}
	return (gl_cpy(&(saved[fd]), &(sizes[fd]), 0,
	               strchr(*lineptr + i, delim)),
	               strlen(*lineptr));
}

//same as ft_getdelim() but reads on top of lineptr instead of ignoring it.
ssize_t	ft_readdelim(char **lineptr, size_t *bufsize, int delim, int fd)
{
	static char		*saved[FD_SETSIZE] = {0};
	static size_t	sizes[FD_SETSIZE] = {0};
	ssize_t			readret;
	size_t			i;

	if (lineptr == NULL || bufsize == NULL || fd < 0
		|| GL_BUFSIZE < 2 || FD_SETSIZE < 3 || saved[fd] == GL_EOF)
		return (-1);
	i = strlen(saved[fd]) + 1;
	if (gl_cpy(lineptr, bufsize, i, saved[fd]) < 0)
		return (-1);
	readret = 0;
	while (strchr(*lineptr + i, delim) == NULL)
	{
		i += readret;
		readret = gl_read(lineptr, bufsize, i, fd);
		if (readret < 0)
			return (-1);
		if (readret == 0)
			return (saved[fd] = GL_EOF, strlen(*lineptr));
	}
	return (gl_cpy(&(saved[fd]), &(sizes[fd]), 0, strchr(*lineptr + i, delim)),
			strlen(*lineptr));
	}
