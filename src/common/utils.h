#ifndef MS_UTILS_H
# define MS_UTILS_H

#include "minishell.h"

// src/common/debug.c:
void ms_log(char *fmt, ...);
void	ms_printenvs(t_environ *env);
void ms_perror(t_shell *sh, int inputidx, char *msg);
void	ms_error_weird_char(int c);


// src/common/utils.c
void		*ms_generic_memset(void *p, void *val, size_t size, size_t n);
size_t		ms_strchrlen(char *str, int c);
uint32_t	ms_round_to_pow_2(uint32_t n);
void		*ms_expand_array(void **old, size_t *oldsize, size_t n);
char		*ms_itoa(char **buffer, size_t *buflen, size_t offset, int n);
size_t		ms_wordlen(char *str);
size_t		ms_tokenlen(char *str, const char *delims); //strstr()

#endif //#ifndef MS_UTILS_H
