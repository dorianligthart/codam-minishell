//rewrite of xxhash.h cause why not

#include <stdint.h>
#include <stddef.h>

#define MS_PRIME1 0x9E3779B1
#define MS_PRIME2 0x85EBCA6B
#define MS_PRIME3 0xC2B2AE35
#define MS_PRIME4 0x27D4EB2F
#define MS_PRIME5 0x165667B1

//25 line rule sucks :/
static inline void	ms_hash_last_step(uint32_t *seed)
{
	*seed ^= *seed >> 15;
	*seed *= MS_PRIME4;
	*seed ^= *seed >> 13;
	*seed *= MS_PRIME3;
	*seed ^= *seed >> 16;
}

uint32_t ms_hash(const void *input, size_t length, uint32_t seed)
{
	uint32_t	chunk;

	seed += MS_PRIME5;
    while (length >= 4)
    {
        chunk = *(uint32_t *)input;
        chunk = (chunk << 8) | (chunk >> 24);
        input += 4;
        length -= 4;
        seed += chunk * MS_PRIME2;
        seed = (seed << 13) | (seed >> 19);
        seed *= MS_PRIME1;
    }
    while (length > 0)
    {
        seed += (*(char *)input) * MS_PRIME5;
        seed = (seed << 11) | (seed >> 21);
        seed *= MS_PRIME1;
        input++;
        length--;
    }
	ms_hash_last_step(&seed);
    return seed;
}

//#include <stdio.h>
//
//int main(void)
//{
//	char *data[64] = {
//			"SHELL=", "WINDOWID=", "COLORTERM=", "XDG_SESSION_PATH=", "I3SOCK=", 
//			"LC_ADDRESS=", "LC_NAME=", "DESKTOP_SESSION=", "LC_MONETARY=",
//			"EDITOR=", "GTK_MODULES=", "XDG_SEAT=", "PWD=", "LOGNAME=",
//			"XDG_SESSION_DESKTOP=", "XDG_SESSION_TYPE=", "XAUTHORITY=",
//			"XDG_GREETER_DATA_DIR=", "MOTD_SHOWN=", "HOME=", "LANG=", "LC_PAPER=",
//			"XDG_CURRENT_DESKTOP=", "XDG_SEAT_PATH=", "XDG_SESSION_CLASS=", "TERM=",
//			"LC_IDENTIFICATION=", "USER=", "COLORFGBG=", "DISPLAY=", "SHLVL=",
//			"LC_TELEPHONE=", "PROMPT_DIRTRIM=", "LC_MEASUREMENT=", "XDG_VTNR=",
//			"XDG_SESSION_ID=", "XDG_RUNTIME_DIR=", "DEBUGINFOD_URLS=" , "LC_TIME=",
//			"GTK3_MODULES=", "BROWSER=", "PATH=", "GDMSESSION=",
//			"DBUS_SESSION_BUS_ADDRESS=", "MAIL=", "LC_NUMERIC=", "_=", NULL,
//	};
//	char	*check[256] = {0};
//
//	printf("hash conflicts:\n");
//	for (size_t i = 0; data[i] != NULL; ++i)
//	{
//		uint32_t	hash = ms_hash(data[i], ms_strclen(data[i], '='), 0) % 256;
//		if (check[hash] != NULL)
//			printf("hash %d: '%s' and '%s' clash!\n", hash, check[hash], data[i]);
//		check[hash] = data[i];
//	}
//	return (0);
//}

