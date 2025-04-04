#include "minishell.h"
#include <stdlib.h> //free()
#include <stdio.h>	//printf()
#include <sys/ioctl.h> //ioctl()
#include <unistd.h> //STDOUT_FILENO
#include <string.h>

#ifndef C_RED
#define C_RED "\033[0;31m"
#endif

#ifndef C_RESET
#define C_RESET "\033[0m"
#endif

void ms_perror(t_shell *sh, int inputidx, char *msg)
{
	struct winsize	w;
	int				column;

	if ((ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) != -1)
		&& inputidx >= 0 && sh->cmdstr != NULL)
	{
		column = (inputidx + strlen(sh->ps1.str));
		fprintf(stderr, "%.*s", w.ws_col, sh->cmdstr + inputidx - (column % w.ws_col));
		fprintf(stderr, "%*c\n", column % w.ws_col, '^');
		fprintf(stderr, "%*c\n", column % w.ws_col, '|');
	}
	fprintf(stderr, C_RED"Error: "C_RESET"%s\n", msg);
}

void	ms_error_weird_char(int c)
{
	const char	*chr_description[32] = {
					NULL,                        "SOH (start of heading)",
					"STX (start of text)",       "ETX (end of text)",
					"EOT (end of transmission)", "ENQ (enquiry)",
					"ACK (acknowledge)",         "BEL '\\a' (bell)",
					"BS  '\\b' (backspace)",     "HT  '\\t' (horizontal tab)",
					"LF  '\\n' (new line)",      "VT  '\\v' (vertical tab)",
					"FF  '\\f' (form feed)",     "CR  '\\r' (carriage ret)",
					"SO  (shift out)",           "SI  (shift in)",
					"DLE (data link escape)",    "DC1 (device control 1)",
					"DC2 (device control 2)",    "DC3 (device control 3)",
					"DC4 (device control 4)",    "NAK (negative ack.)",
					"SYN (synchronous idle)",    "ETB (end of trans. blk)",
					"CAN (cancel)",              "EM  (end of medium)",
					"SUB (substitute)",          "ESC (escape)",
					"FS  (file separator)",      "GS  (group separator)",
					"RS  (record separator)",    "US  (unit separator)",
	};

	if (c > 0 && c < ' ')
		printf("Error: encountered character: %#X:%s\n",
				c, chr_description[c]);
}

