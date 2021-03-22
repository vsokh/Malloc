CC = gcc
CFLAGS = -Wall -shared -undefined dynamic_lookup
LIBFT = Libft/libft.a
SRC = src/malloc.c src/utils.c
INC = inc

MD := malloc_debug

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PREFIX = libft_malloc
NAME = $(PREFIX)_$(HOSTTYPE).so

all: $(LIBFT)
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

run: all
	./$(NAME)

dclean:
	rm $(MD)

debug: $(LIBFT)
	gcc -D DEBUG $(SRC) -I$(INC) -o $(MD)

bonus:
	@echo "There are no bonuses yet."


