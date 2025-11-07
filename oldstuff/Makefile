CFLAGS = -fsanitize=address
all:
	cc -g $(CFLAGS) -o simple-shell.out simple-shell.c
	cc -g $(CFLAGS) -o dup.out dup.c
clean:
	rm -f ./simple-shell.out ./dup.out

.PHONY: all clean
