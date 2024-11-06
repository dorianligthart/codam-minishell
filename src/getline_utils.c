//util functions of getline.c
//defined in getline.h

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#define GL_BUFSIZE 1024

ssize_t	ft_getline_split(char **dst, char **src, int delim)
{
	ptrdiff_t	index;
	char		*ptr;
	size_t		src_rest;

	ptr = strchr(*src, delim);
	if (ptr[1] == '\0')
	{
		*dst = *src;
		*src = NULL;
		return (strlen(*dst));
	}
	index = ptr - *src + 1;
	src_rest = strlen(*src + index);
	if (src_rest > 0)
	{
		ptr = malloc(src_rest + 1);
		if (ptr == NULL)
			return (-1);
		(ptr)[src_rest] = '\0';
		memcpy(ptr, *src + index + 1, src_rest);
	}
	(*src)[index] = '\0';
	*dst = *src;
	*src = ptr;
	return (index);
}

ssize_t	ft_getline_read(size_t *n, int fd, char **saved)
{
	ssize_t	readret;
	size_t	savedlen;
	char	*result;

	savedlen = 0;
	if (saved[fd] != NULL)
		savedlen = strlen(saved[fd]);
	if (saved[fd] == NULL || *n < savedlen + GL_BUFSIZE)
	{
		*n = *n * 2 + (*n == 0) * GL_BUFSIZE;
		result = malloc(*n);
		if (result == NULL && *n != GL_BUFSIZE)
			free(saved[fd]);
		if (result == NULL)
			return (-1);
		memcpy(result, saved[fd], savedlen);
		if (saved[fd] != NULL)
			free(saved[fd]);
		saved[fd] = result;
	}
	readret = read(fd, saved[fd] + savedlen, *n - savedlen - 1);
	if (readret >= 0)
		saved[fd][savedlen + readret] = '\0';
	return (readret);
}

ssize_t	ft_getline_read_ontop(size_t *n, int fd, char **saved)
{
	ssize_t	readret;
	size_t	savedlen;
	char	*result;

	savedlen = 0;
	if (saved[fd] != NULL)
		savedlen = strlen(saved[fd]);
	if (saved[fd] == NULL || *n < savedlen + GL_BUFSIZE)
	{
		*n = *n * 2 + (*n == 0) * GL_BUFSIZE;
		result = malloc(*n);
		if (result == NULL && *n != GL_BUFSIZE)
			free(saved[fd]);
		if (result == NULL)
			return (-1);
		memcpy(result, saved[fd], savedlen);
		if (saved[fd] != NULL)
			free(saved[fd]);
		saved[fd] = result;
	}
	readret = read(fd, saved[fd] + savedlen, *n - savedlen - 1);
	if (readret >= 0)
		saved[fd][savedlen + readret] = '\0';
	return (readret);
}
