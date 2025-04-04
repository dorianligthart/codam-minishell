#include "../getline.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char 	*line;
	size_t	n;
	ssize_t	ret;

	line = NULL;
	do {
		write(1, "shell >", 7);
		ret = ft_readline(&line, &n, 0);
		if (ret < 0)
			return (1);
		write(1, line, strlen(line));
	} while (ret != 0);
	free(line);
	return (0);
}
