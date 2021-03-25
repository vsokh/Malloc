CC = gcc
CFLAGS = -Wall -shared -undefined dynamic_lookup
LIBFT = Libft/libft.a
SRC = src/malloc.c src/utils.c src/free.c
INC = inc

MD := malloc_debug

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PREFIX = libft_malloc
NAME = $(PREFIX)_$(HOSTTYPE).so

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -I$(INC) -o $(NAME) $(LIBFT) $(SRC)
	ln -sf $(NAME) $(PREFIX).so

$(LIBFT):
	make -C Libft

clean:
	unlink $(PREFIX).so
	make clean -C Libft

fclean: clean
	make fclean -C Libft
	rm $(NAME)

re: fclean all

tclean:
	rm test/test

test: $(LIBFT) $(NAME)
	gcc -L. test/main.c -o test/test -lft_malloc
	./run.sh ./test/test

.PHONY: all clean fclean re debug dclean test


