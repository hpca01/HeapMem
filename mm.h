#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

static size_t SYS_PAGE_SIZE = 0;
static container_for_families_t *first_container = NULL;
const size_t MAX_STRUCT_NAME = 32;

/// what is max # of family you can fit into 1 memory page? (SYS_PAGE_SIZE - sizeof(container *))/ sizeof(family)
#define MAX_FAM_PER_PAGE \
    (SYS_PAGE_SIZE - sizeof(container_for_families_t *) / sizeof(family_t))

/// Macro for iterating through the container families, note doesn't include traversing to next container
#define ITERATE_FAMILY_BEGIN(container_for_families_ptr, curr)     \
    {                                                              \
        uint32_t count = 0;                                        \
        for (curr = (family_t *)container_for_families_t->page[0]; \
             curr->struct_size && count < MAX_FAM_PER_PAGE;        \
             curr++, count++)                                      \
        {

#define ITERATE_FAMILY_END(container_for_families_ptr, curr) \
    }                                                        \
    }

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
// page
static void *get_page_from_kernel(int units);
static void purge_page_from_kernel(void *page, int units);
//family
void instantiate_new_family(char *struct_name, uint32_t size);