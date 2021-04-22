# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 18:38:50 by vsokolog          #+#    #+#              #
#    Updated: 2021/04/20 16:16:12 by vsokolog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC
LDFLAGS = -shared

INCL = -I inc
DEPS = inc/malloc.h
SRCDIR = src
OBJDIR = obj
SRC = malloc.c free.c realloc.c utils.c tinysmall.c large.c
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

$(NAME): $(DEPS) $(OBJ)
	$(CC) $(LDFLAGS) $(INCL) -o $@ $(OBJ)
	ln -sf $(NAME) $(PREFIX).so
	@echo ${GREEN}$(NAME) compiled!${NOCOLOR}

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(LIBFT)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCL) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)
	make clean -C test

fclean: clean
	rm -f $(PREFIX).so
	rm -f $(NAME)

re: fclean all

test: all
	make -C test

.PHONY: all clean fclean re test

