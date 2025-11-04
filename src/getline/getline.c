//definitions of getline.h
//util functions located in getline_utils.c
#include <stdio.h>

#include <stdlib.h>     //malloc() free()
#include <stdbool.h>    //bool, true, false
#include <unistd.h>     //read()
#include <string.h>     //memcpy(), strlen(), memset()

/* GETDELIM_EOF '(void *)-1' which is a hacky way to let the next call of
                getdelim() or readdelim() know EOF has been reached on that fd.
GETDELIM_BUFFER all buffer sizes used in this program is a multiplication of
                GETDELIM_BUFFER and has to be bigger or equal than 2.
FD_SETSIZE      is the maximum number of open file descriptors per program,
                starting from 4 up to FD_SETSIZE. (4 meaning index 3)
                If not, this libraries functions will return -1.    */
#define GETDELIM_EOF (void *)-1
#ifndef GETDELIM_BUFFER
# define GETDELIM_BUFFER 32
#endif
#include <sys/select.h> //definition of FD_SETSIZE

typedef struct t_getline_vars
{
	ssize_t	readret;
	size_t	offset;
	char	*split;
} t_getline_vars;

static size_t	safe_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		++i;
	return (i);
}

//Tries to append-read from filedescriptor fd to *lineptr.
//returns: read(2) return-value or -1 in case of malloc(3) error.
static ssize_t	getdelim_read(char **lineptr, size_t *bufsize,
                              size_t offset, int fd)
{
	ssize_t	readret;
	char	*realloc;

	if (*lineptr == NULL || offset + GETDELIM_BUFFER > *bufsize)
	{
		*bufsize = ((offset / GETDELIM_BUFFER + 2) * GETDELIM_BUFFER);
		realloc = malloc(*bufsize);
		if (realloc == NULL)
			return (-1);
		memcpy(realloc, *lineptr, offset);
		realloc[*bufsize - 1] = '\0';
		free(*lineptr);
		*lineptr = realloc;
	}
	readret = read(fd, *lineptr + offset, GETDELIM_BUFFER - 1);
	if (readret >= 0)
		(*lineptr)[offset + readret] = '\0';
	return (readret);
}

//copies src to dst while making sure dst is big enough.
//returns length of dst and src.
static ssize_t	getdelim_copy(char **dst, size_t *dstsize,
	                          char *src, bool keep_dst)
{
	const size_t	srclen = safe_strlen(src);
	const size_t	dstlen = safe_strlen(*dst) * keep_dst;
	char			*realloc;
	
	if (*dst == NULL || *dstsize <= dstlen + srclen)
	{
		*dstsize = ((dstlen + srclen) / GETDELIM_BUFFER + 1) * GETDELIM_BUFFER;
		realloc = malloc(*dstsize);
		if (realloc == NULL)
			return (-1);
		realloc[*dstsize - 1] = '\0';
		if (dst != NULL)
		{
			memcpy(realloc, *dst, dstlen);
			free(*dst);
		}
		*dst = realloc;
	}
	if (src != NULL)
		memcpy(*dst + dstlen, src, srclen);
	(*dst)[dstlen + srclen] = '\0';
	if (src != NULL)
		*src = '\0';
	return (dstlen + srclen);
}

//returns the amount of bytes read from fd until delim was found, or -1 on error
ssize_t ft_getdelim(char **lineptr, size_t *bufsize, int delim, int fd)
{
	static char		*saved[FD_SETSIZE] = {0};
	static size_t	sizes[FD_SETSIZE] = {0};
	t_getline_vars	v;

	memset(&v, '\0', sizeof(t_getline_vars));
	if (lineptr == NULL || bufsize == NULL || fd < 0
		|| GETDELIM_BUFFER < 2 || FD_SETSIZE < 3 || saved[fd] == GETDELIM_EOF
		|| getdelim_copy(lineptr, bufsize, saved[fd], false) < 0)
		return (-1);
	while (saved[fd] != GETDELIM_EOF
           && strchr(*lineptr + v.offset, delim) == NULL)
	{
		v.offset += v.readret;
		v.readret = getdelim_read(lineptr, bufsize, v.offset, fd);
		if (v.readret < 0)
			return (-1);
		if (v.readret == 0)
			return (saved[fd] = GETDELIM_EOF, safe_strlen(*lineptr));
	}
	v.split = strchr(*lineptr + v.offset, delim) + 1;
	if (*v.split != '\0')
		return (getdelim_copy(&(saved[fd]), &(sizes[fd]), v.split, false));
	return (v.split - *lineptr + v.offset);
}

//same as ft_getdelim() but reads on the end of lineptr instead of from start
ssize_t	ft_readdelim(char **lineptr, size_t *bufsize, int delim, int fd)
{
	static char		*saved[FD_SETSIZE] = {0};
	static size_t	sizes[FD_SETSIZE] = {0};
	t_getline_vars	v;

	memset(&v, '\0', sizeof(t_getline_vars));
	if (lineptr == NULL || bufsize == NULL || fd < 0
		|| GETDELIM_BUFFER < 2 || FD_SETSIZE < 3 || saved[fd] == GETDELIM_EOF
		|| getdelim_copy(lineptr, bufsize, saved[fd], true) < 0)
		return (-1);
	v.offset = safe_strlen(*lineptr);
	while (strchr(*lineptr + v.offset, delim) == NULL)
	{
		v.offset += v.readret;
		v.readret = getdelim_read(lineptr, bufsize, v.offset, fd);
		if (v.readret < 0)
			return (-1);
		if (v.readret == 0)
			return (saved[fd] = GETDELIM_EOF, strlen(*lineptr));
	}
	v.split = strchr(*lineptr + v.offset, delim) + 1;
	if (*v.split != '\0')
		return (getdelim_copy(&(saved[fd]), &(sizes[fd]), v.split, false));
	return (v.split - *lineptr + v.offset);
}
