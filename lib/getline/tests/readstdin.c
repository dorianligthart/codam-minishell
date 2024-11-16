#include "../getline.h"
#include <stdlib.h>

int main(void)
{
	char 	*line;
	size_t	n;

	line = NULL;
	ft_getline(&line, &n, 0);
	free(line);
	return (0);
}
