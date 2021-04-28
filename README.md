# Malloc
The project is a thread-safe memory management shared library that wraps [mmap](https://man7.org/linux/man-pages/man2/mmap.2.html) and [munmap](https://man7.org/linux/man-pages/man2/mmap.2.html) system calls.
It consists of a caching allocator, First-Fit allocation algorithm, and so-called explicit doubly linked list for keeping track of reserved/released blocks of memory and simplifies their splitting/coalescing.

The list of implemented functions:
```
void	*malloc(size_t size)
void	*realloc(void *ptr, size_t size)
void	free(void *ptr)

/* Prints to the standard output information about allocated memory zones */
void	show_alloc_mem(void)
```

## Install & Build & Run
```
git clone https://github.com/vsokh/malloc.git && \
cd malloc && \
make test
```

## Author
vsokolog
