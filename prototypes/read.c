#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	char buffer[64]; //TODO: make this a never ending buffer using realloc or
					 //sumthing.

	ssize_t	readreturn = 1;
	while (readreturn >= 0)
	{
		write(1, "> ", 2);
		readreturn = read(0, buffer, 64);
		if (readreturn < 0)
			return 1;
		buffer[readreturn = '\0'];
		if (strchr(buffer, '\"'))
			return (0);
	}
	return 0;
}
