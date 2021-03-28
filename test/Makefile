CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INCL = -I ../inc -I ../libft/inc

YELLOW = '\033[33m'
NOCOLOR = '\033[0m'

TESTS = test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test13v2 test14 test15 test16 test17 42test1 42test2 42test7

all: $(TESTS)
	@echo ${YELLOW}[Running $(TESTS)]${NOCOLOR}
	@./run.sh $(TESTS)

clean:
	rm -rf $(addsuffix .dSYM, $(TESTS))
	rm -rf $(TESTS)

$(TESTS): %: %.c
	@$(CC) $(CFLAGS) -L.. -lft_malloc $(INCL) -o $@ $<
