#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

size_t	ms_strchrlen(char *str, int c)
{
	size_t	ret;

	ret = 0;
	while (str[ret] && str[ret] != c)
		ret++;
	return (ret);
}

void	*ms_expand_array(void **old, size_t *oldsize, size_t size, size_t n)
{
	void *new;

	new = malloc(n * size);
	if (old != NULL && new != NULL)
		memcpy(new, old, *oldsize * size);
	*oldsize = n;
	*old = new;
	return (new);
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

//returns -1 if delims wasn't found.
size_t	len_until_delims(char *str, const char *delims)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (str[++y])
	{
		x = -1;
		while (delims[++x])
			if (str[y] == delims[x])
				return (y);
	}
	return (-1);
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
char	*ms_itoa(char *buffer, size_t buflen, int n)
{
	size_t	index;
	long	n_long;

	n_long = (long)n;
	if (n < 0)
		n_long *= -1;
	index = intlen(n, 10);
	if (buflen < index)
		buffer = (char *)malloc((index + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[index] = 0;
	while (index--)
	{
		buffer[index] = (n_long % 10) + '0';
		n_long = n_long / 10;
	}
	if (n < 0)
		buffer[0] = '-';
	return (buffer);
}

