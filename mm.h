#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

static size_t SYS_PAGE_SIZE = 0;
const size_t MAX_STRUCT_NAME = 32;

//what is max # of family you can fit into 1 memory page? (SYS_PAGE_SIZE - sizeof(container *))/ sizeof(family)
#define MAX_FAM_PER_PAGE (SYS_PAGE_SIZE - sizeof(container_for_families_t *) / sizeof(family_t))

/// Struct for registering information from userspace program
// name - name of struct max size 32
// struct_size - size of struct being requested by user space
typedef struct family
{
    char name[MAX_STRUCT_NAME];
    uint32_t struct_size;
} family_t;

/// Struct for registering sets of family structs.
// *next - next container
// page[0] - pointer to the array of family objects where data resides.
typedef struct container_for_families
{
    struct container_for_families *next;
    family_t page[0];

} container_for_families_t;

// get page size
void init();
static void *get_page_from_kernel(int units);

static void purge_page_from_kernel(void *page, int units);