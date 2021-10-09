CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INCL = -I ../inc

YELLOW = "\033[33m"
NOCOLOR = "\033[0m"

TESTS = malloc_test free_test realloc_test test0 test1 test2 test3 test4 test5 test6 test7
# TESTS = test1 test2

all: $(TESTS)
	@echo ${YELLOW}Running [$(TESTS)]${NOCOLOR}
	@./run_tests.sh $(TESTS)

clean:
	@echo ${YELLOW}Cleaning $(TESTS)${NOCOLOR}
	@rm -rf $(addsuffix .dSYM, $(TESTS))
	@rm -rf $(TESTS)

re: clean all

$(TESTS): %: %.c
	@echo ${YELLOW}Compiling $<${NOCOLOR}
	@$(CC) -L.. $(CFLAGS) $(INCL) -o $@ $< -lft_malloc -pthread
