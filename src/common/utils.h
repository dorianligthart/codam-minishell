#ifndef MS_UTILS_H
# define MS_UTILS_H

#include "minishell.h"

//utils.c
size_t		ms_strchrlen(char *str, int c);
uint32_t	ms_round_to_pow_2(uint32_t n);
void		*ms_expand_array(void **old, size_t *oldsize, size_t size, size_t n);
char		*ms_itoa(char *buffer, size_t buflen, int n);

//free.c:
void		ms_free(t_shell *sh);
size_t		ms_wordlen(char *str);
size_t		ms_tokenlen(char *str, const char *delims); //strstr()

#endif //#ifndef MS_UTILS_H
