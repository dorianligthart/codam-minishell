NAME	:= minishell
HEADER	:= ./include
SRC		:= $(shell find src/ -maxdepth 1 -type f -regex ".*\.c")
RM		:= rm -f
CFLAGS	:= -g -Wall -Wextra#TODO: -Werror
LINK	:= -lreadline -lncurses

# prototypes are one file test/showcase programs.
PROTO	:= $(shell find prototypes/ -maxdepth 1 -type f -regex ".*\.c")
PROTOEX = $(PROTO:.c=)

%: %.c
	gcc $(CFLAGS) -I$(HEADER) -o $@ $< $(LINK)

$(NAME): $(SRC)
	gcc $(CFLAGS) -I$(HEADER) -o $(NAME) $(SRC) $(LINK)

extra: $(PROTOEX)	
all: $(NAME) extra
clean:
	$(RM) $(NAME)
	$(RM) $(PROTOEX)
fclean: clean
re: clean all
