all: ./cmd_search.out ./pipes_demo.out ./list_bin_files.out ./signal_echo.out ./wildcard.out ./keysymprint.out

./keysymprint.out: ./keysymprint.c
	cc -g -o $@ $^ && valgrind --leak-check=full --show-leak-kinds=all ./keysymprint.out

./wildcard.out: ./wildcard.c
	cc -g -o $@ $^ && valgrind --leak-check=full --show-leak-kinds=all ./wildcard.out

./signal_echo.out: ./signal_echo.c
	cc -g -o $@ $^ -lreadline && valgrind --leak-check=full --show-leak-kinds=all ./signal_echo.out

./list_bin_files.out: ./list_bin_files.c
	cc -g -o $@ $^ && valgrind --leak-check=full --show-leak-kinds=all ./list_bin_files.out .

./cmd_search.out: ./cmd_search.c
	cc -g -o cmd_search.out cmd_search.c \
	   	&& valgrind --leak-check=full --show-leak-kinds=all ./cmd_search.out ls

./pipes_demo.out: ./pipes_demo.c
	cc -g -o pipes_demo.out pipes_demo.c && ./pipes_demo.out

clean:
	rm -f ./cmd_search.out ./pipes_demo.out ./list_bin_files.out ./signal_echo.out ./wildcard.out ./keysymprint.out

.PHONY: all clean ./pipes_demo.out ./cmd_search.out ./list_bin_files.out ./signal_echo.out ./wildcard.out ./keysymprint.out
