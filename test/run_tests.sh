#!/bin/sh

export DYLD_LIBRARY_PATH=..
export DYLD_INSERT_LIBRARIES="../libft_malloc.so"

RED="\033[0;31m"
GREEN="\033[0;32m"
NOCOLOR="\033[0m"

for test in "$@"; do
	if ./"$test" > /dev/null; then
		echo "$test: ${GREEN}OK${NOCOLOR}"
	else
		echo "$test: ${RED}FAIL${NOCOLOR}"
	fi
done
