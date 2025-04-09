NAME        := minishell
CC          := gcc
BASICFLAGS  := -ggdb -Wall -Wextra -Werror
CFLAGS      := -c $(BASICFLAGS)
LFLAGS      := $(BASICFLAGS) -lncurses -lreadline #-fsanitize=address
# TODO: get rid of $(shell)
HEADER_DIRS := $(shell find ./src -type f -regex '.*\.h' | grep -o '.*/' | grep -v 'test' | sed 's|.\/$|||' | uniq)
INCLUDES    := $(addprefix -I, $(HEADER_DIRS))
SRCS        := $(shell find src/ -type f -regex '.*\.c' | grep -v 'test')
OBJS        := $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(LFLAGS) $(INCLUDES) -o $@ $(OBJS)

all: $(NAME)
instant: $(SRCS)
	$(CC) $(LFLAGS) $(INCLUDES) -o $(NAME) $(SRCS)
	valgrind --log-file='.vgcore' --leak-check=full --show-leak-kinds=all ./minishell || cat .vgcore
clean:
	rm $(NAME) $(OBJS) $(LEXER) $(ENVIRON)
fclean:
	rm -f $(NAME) $(OBJS) $(LEXER) $(ENVIRON)
re: fclean all

# development/testing:
tests: $(LEXER) $(ENVIRON)
tags:
	ctags -R src/*

LEXER := src/test/lexer
$(LEXER): src/lexer.c src/test/lexermain.c 
	$(CC) $(TESTFLAGS) -o $@ $< 

ENVIRON := src/test/environ
$(ENVIRON): src/environ.c src/test/environmain.c 
	$(CC) $(TESTFLAGS) -o $@ $< 

.PHONY: all clean fclean re tests tags 
