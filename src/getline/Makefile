NAME	 := getline.a
CFLAGS	 := -Wall -Wextra -Werror -Wunused -g
CC       := gcc
SRC		 := $(shell find -maxdepth 1 -type f -regex ".*\.c")
OBJ		 := $(SRC:.c=.o)
TESTS    := $(shell find tests/ -maxdepth 1 -type f -regex ".*\.c")
TESTS_EX := $(TESTS:.c=.out)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

tests: $(TESTS_EX)
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
all: $(NAME) tests
clean:
	rm -f $(OBJ)
	rm -f $(TESTS_EX)
fclean: clean
	rm -f $(NAME)
re: clean all

.PHONY: tests all clean fclean re
