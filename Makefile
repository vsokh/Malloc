# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 18:38:50 by vsokolog          #+#    #+#              #
#    Updated: 2021/04/07 15:50:16 by vsokolog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
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
YELLOW = '\033[33m'
GREEN = '\033[0;32m'
NOCOLOR = '\033[0m'

all: $(NAME)

$(NAME): $(LIBFT) $(DEPS) $(OBJ)
	$(CC) $(LDFLAGS) -Llibft -lft $(INCL) -o $@ $(OBJ)
	ln -sf $(NAME) $(PREFIX).so
	@echo ${GREEN}$(NAME) compiled!${NOCOLOR}

$(LIBFT):
	make -C libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(LIBFT)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCL) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)
	make clean -C libft
	make clean -C test

fclean: clean
	make fclean -C libft
	rm -f $(PREFIX).so
	rm -f $(NAME)

re: fclean all

norm:
	@echo ${YELLOW}[Norminetting $(NAME)]${NOCOLOR}
	~/.norminette/norminette.rb src/* inc/* 
	make norm -C libft

test: all
	make -C test

.PHONY: all clean fclean re test norm

