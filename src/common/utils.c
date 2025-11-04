#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

//assuming sizeof(p) == n * size
void *ms_generic_memset(void *p, void *val, size_t size, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		memcpy(((char *)p + (i * size)), val, size);
	return (p);
}

//returns -1 if delims wasn't found.
size_t	ms_strchrslen(char *str, const char *delims)
{
	size_t	y;

	y = -1;
	while (str[++y])
		if (strchr(delims, str[y]) != NULL)
			return (y);
	return (-1);
}

size_t	ms_strchrlen(char *str, int c)
{
	size_t	ret;

	ret = 0;
	while (str[ret] && str[ret] != c)
		ret++;
	return (ret);
}

void	*ms_expand_array(void **src, size_t *srcsize, size_t newsize)
{
	printf("about to malloc(%zu * %zu), old size=%zu\n", newsize, sizeof(**src), *srcsize);
	void *dst;

	dst = malloc(newsize * sizeof(**src));
	if (src != NULL && dst != NULL)
	{
		memcpy(dst, *src, *srcsize * sizeof(**src));
		memset(dst + *srcsize, '\0', newsize - *srcsize);
		free(*src);
	}
	*srcsize = newsize;
	*src = dst;
	return (dst);
}

size_t	ms_wordlen(char *str)
{
	size_t	i;

	if ((*str < 'a' && *str > 'z')
		&& (*str < 'A' && *str > 'Z')
		&& *str != '_')
		return (0);
	i = 0;
	while ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_') {
		i++;
	}
	return (i);
}

uint32_t	ms_round_to_pow_2(uint32_t n)
{
	n--;
	n|=n>>1;
	n|=n>>2;
	n|=n>>4;
	n|=n>>8;
	n|=n>>16;
	n++;
	return (n);
}

static int	intlen(int n, int base)
{
	int	intlen;

	intlen = 1;
	while (-base >= n || n >= base)
	{
		n /= base;
		intlen++;
	}
	if (n < 0)
		intlen++;
	return (intlen);
}

//reallocs if necessary;
bool	ms_itoa(char **buf, size_t *bufsize, size_t offset, int integer)
{
	size_t	len;
	long	longint;

	longint = (long)integer;
	if (integer < 0)
		longint *= -1;
	len = intlen(integer, 10);
	if (*bufsize < len + offset)
	{
		free(*buf);
		*buf = (char *)malloc((len + offset + 1) * sizeof(char));
		if (!*buf)
			return (NULL);
	}
	(*buf)[len + offset] = 0;
	while (len--)
	{
		(*buf)[offset + len] = (longint % 10) + '0';
		longint = longint / 10;
	}
	if (integer < 0)
		(*buf)[offset] = '-';
	return (*buf);
}

