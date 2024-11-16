#include "getline.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(void)
{
	char	*line = NULL;
	size_t	n = 0;
//	getline(&line, &n, stdin);
//	printf("main() retrieved: %s", line);
//	free(line);
//	return 0;

	ssize_t	readreturn = 1;
	while (readreturn > 0)
	{
		readreturn = ft_getline(&line, &n, 0);
		if (readreturn < 0)
			break ;
		printf("main() retrieved: %s", line);
	}
	free(line);
	return (0);
}
