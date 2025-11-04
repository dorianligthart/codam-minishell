NAME        := minishell
MAIN        := src/main.o
CC          := gcc
#TODO: build with -Wunused-parameter/variable
BASICFLAGS  := -ggdb -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable
CFLAGS      := -c $(BASICFLAGS)
LFLAGS      := $(BASICFLAGS) -lncurses -lreadline
# TODO: get rid of $(shell)
HEADER_DIRS := $(shell find ./src -type f -regex '.*\.h' | grep -o '.*/' | grep -v '/.*\.h' | sort  | uniq)
INCLUDES    := $(addprefix -I, $(HEADER_DIRS))
SRCS        := $(shell find src/ -type f -regex '.*\.c' | grep -v 'main')
OBJS        := $(SRCS:.c=.o)

# development/testing:
TEST_SRCS := $(shell find test -type f -regex '.*\.c')
TEST_BINS := $(TEST_SRCS:.c=.out)
test/%: $(OBJS) test/%.c  
	$(CC) $(BASICFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS)
tests: $(TEST_BINS)
tags:
	ctags -R src/*


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

$(NAME): $(OBJS) $(MAIN)
	$(CC) $(INCLUDES) $(LFLAGS) -o $@ $^  

all: $(NAME) $(TEST_BINS)
	./minishell
clean:
	rm -f $(MAIN) $(OBJS) $(TEST_BINS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re instant test tags 
