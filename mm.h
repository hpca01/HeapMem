#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/mman.h>

static void *get_page_from_kernel(int units);

static void purge_page_from_kernel(void *page, int units);