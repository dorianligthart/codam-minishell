NAME	:= minishell
HEADER	:= ./include
SRC		:= $(shell find src/ -maxdepth 1 -type f -regex ".*\.c")
RM		:= rm -f
CFLAGS	:= -Wall -Wextra #TODO: -Werror
LINK	:= -lreadline

$(NAME): $(SRC)
	gcc -o $(NAME) $(LINK) -I$(HEADER) $(SRC) 
all: $(NAME)
clean:
	$(RM) $(NAME)
fclean: clean
re: clean all
