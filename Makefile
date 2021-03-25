# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 18:38:50 by vsokolog          #+#    #+#              #
#    Updated: 2021/03/25 18:38:50 by vsokolog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -shared
LIBFT = libft/libft.a

INCL = -I inc -I libft/inc
DEPS = inc/malloc.h libft/inc/libft.h
SRCDIR = src
OBJDIR = obj
SRC = malloc.c utils.c free.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PREFIX = libft_malloc
NAME = $(PREFIX)_$(HOSTTYPE).so

RED = '\033[0;31m'
YELLOW = "\033[33m"
GREEN = '\033[0;32m'
NOCOLOR = '\033[0m'

all: $(NAME)

$(NAME): $(LIBFT) $(DEPS) $(OBJ)
	$(CC) $(LDFLAGS) -Llibft -lft $(INCL) -o $@ $(OBJ)
	ln -sf $(NAME) $(PREFIX).so
	@echo ${GREEN}$(NAME) has successfully compiled!${NOCOLOR}

$(LIBFT):
	make -C libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(LIBFT)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCL) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)
	make clean -C libft

fclean: clean tclean
	make fclean -C libft
	rm -f $(PREFIX).so
	rm -f $(NAME)

re: fclean all

tclean:
	rm -f test/test

test: all
	@echo ${YELLOW}[Checking $(NAME)]${NOCOLOR}
	gcc -L. -lft_malloc test/main.c -o test/test 
	./run.sh ./test/test

norm:
	@echo ${YELLOW}[Norminetting $(NAME)]${NOCOLOR}
	~/.norminette/norminette.rb src/* inc/* 
	make norm -C libft

.PHONY: all clean fclean re debug dclean test


