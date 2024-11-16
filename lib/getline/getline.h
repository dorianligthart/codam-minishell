#ifndef GETLINE_H
# define GETLINE_H

#include <sys/types.h>

//reads a string from fd until delim or EOF is found.
//returns the bytes until delim, or -1 on malloc(3)/read(2) error.
ssize_t ft_getdelim(char **lineptr, size_t *n, int delim, int fd);
ssize_t	ft_getline(char **lineptr, size_t *n, int fd);

//instead of returning one line, read a next line ontop of *lineptr.
//each call gets one more line.
ssize_t	ft_readdelim(char **lineptr, size_t *n, int delim, int fd);
ssize_t	ft_readline(char **lineptr, size_t *n, int fd);

//RETURNS a pointer to the next line from fd,
//        or NULL on error or 1 sized malloc(3) byte on EOF.
char	*get_next_line(int fd);

#endif //GETLINE_H
