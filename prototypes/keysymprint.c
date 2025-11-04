//print your stdin as ascii

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char	bufferin[1024];
	int		ret;

	bzero(bufferin, 1024);
	write(1, "write some escape keys> \n", 26);
	ret = read(STDIN_FILENO, bufferin, 1024);
	if (ret < 0) return (1);

	write(STDOUT_FILENO, "showing ascii: [", 6);
	size_t i = 0;
	while (bufferin[i])
	{
		if (isprint(bufferin[i]) && isblank(bufferin[i]) == 0)
			printf("%c, ", bufferin[i]);
		else 
			printf("%d, ", bufferin[i]);
		i++;
	}
	fflush(stdout);
	write(STDOUT_FILENO, "\b\b]\n", 4);
	return (0);
}
