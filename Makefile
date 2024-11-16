NAME	:= minishell
CC      := gcc
RM		:= rm -f
CFLAGS	:= -g -Wall -Wextra -Werror
LINK	:= -lreadline -lncurses

# source files in ./src/
SRC		:= $(shell find src/ -maxdepth 1 -type f -regex ".*\.c" | sort)
# prototypes are one-file testprograms in ./prototypes/
PROTO	:= $(shell find prototypes/ -maxdepth 1 -type f -regex ".*\.c")
PROTOEX := $(PROTO:.c=)
# header directory search ./
H_DIRS	:= $(shell find -type f -regex ".*\.h" | grep -o '.*/' \
                 | sed 's|.\/$|||' | uniq)
INCLUDE := $(addprefix -I, $(H_DIRS))
# library *.a files in ./lib/
LIBS 	:= $(shell find ./lib/ -maxdepth 1 -type d | tail -n +2)
#          suffixes basename to itself, then suffixes "*.a".
LIBS_A	:= $(addsuffix /$(shell basename $(LIBS)).a, $(LIBS))

%: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $< $(LIBS_A) $(LINK)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(SRC) $(LIBS_A) $(LINK)

$(LIBS_A): $(LIBS)
	make all -C $(LIBS)

all: $(LIBS_A) $(NAME)
clean:
	make clean -C $(LIBS)
	$(RM) $(NAME)
	$(RM) $(PROTOEX)
fclean: clean
	$(RM) $(LIB_A)
re: fclean all
proto: $(PROTOEX)
prototype: proto

.PHONY: all proto clean fclean re cleanlibs
