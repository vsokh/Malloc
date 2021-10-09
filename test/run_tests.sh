#!/bin/sh

export DYLD_LIBRARY_PATH=..
export DYLD_INSERT_LIBRARIES="../libft_malloc.so"
# export DYLD_FORCE_FLAT_NAMESPACE=1

RED="\033[0;31m"
GREEN="\033[0;32m"
NOCOLOR="\033[0m"

for test in "$@"; do
	if /usr/bin/time -l ./"$test"; then
	# if ./"$test"; then
		echo "$test: ${GREEN}OK${NOCOLOR}"
	else
		echo "$test: ${RED}FAIL${NOCOLOR}"
	fi
done

