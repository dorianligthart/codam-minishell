#include "envs.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

#define MS_ENVSIZE 64
#define MS_HASHMULT 4

static bool	ms_envrealloc_hash(t_environ *src, t_environ *dst, size_t newsize)
{
	dst->table1 = calloc(newsize * MS_HASHMULT, sizeof(int));
	if (dst->table1 == NULL)
		return (false);
	dst->table2 = calloc(newsize * MS_HASHMULT, sizeof(int));
	if (dst->table2 == NULL)
		return (free(dst->table1), false);
	dst->table3 = calloc(newsize * MS_HASHMULT, sizeof(int));
	if (dst->table3 == NULL)
		return (free(dst->ptr), free(dst->ismalloced),
				free(dst->table1), free(dst->table2), false);
	free(src->table1);
	free(src->table2),
	free(src->table3);
	src->table1 = dst->table1;
	src->table2 = dst->table2;
	src->table3 = dst->table3;
	src->tablesize = newsize * MS_HASHMULT;
	return (true);
}

bool	ms_envrealloc(t_environ *src, size_t newsize)
{
	t_environ	dst;

	dst.ptr = calloc(newsize, sizeof(char *));
	if (dst.ptr == NULL)
		return (false);
	dst.ismalloced = calloc(newsize, sizeof(bool));
	if (dst.ismalloced == NULL)
		return (free(dst.ptr), false);
	dst.islocal = calloc(newsize, sizeof(bool));
	if (dst.islocal == NULL)
		return (free(dst.ptr), free(dst.ismalloced), false);
	memcpy(dst.ptr, src->ptr, src->size);
	memcpy(dst.ismalloced, src->ismalloced, src->size);
	memcpy(dst.islocal, src->islocal, src->size);
	if (src->ptr != NULL && src->ismalloced != NULL && src->islocal != NULL)
		(free(src->ptr), free(src->ismalloced), free(src->islocal));
	src->ptr = dst.ptr;
	src->ismalloced = dst.ismalloced;
	src->islocal = dst.islocal;
	src->size = newsize;
	if (ms_envrealloc_hash(src, &dst, newsize) == false)
		return (free(dst.ptr), free(dst.ismalloced), free(dst.islocal), false);
	return (true);
}
