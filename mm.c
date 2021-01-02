#include "mm.h"

void init()
{
    SYS_PAGE_SIZE = getpagesize();
}

static void *get_page_from_kernel(int units)
{
    void *addr = mmap(NULL, units * SYS_PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0); //not backed by a file and private

    if (addr == MAP_FAILED)
    {
        printf("Could not allocate page\n");
        return NULL;
    }
    memset(addr, 0, units * SYS_PAGE_SIZE);
    return addr;
}

static void purge_page_from_kernel(void *page, int units)
{
    if (munmap(page, units * SYS_PAGE_SIZE) != 0)
    {
        printf("Error: Cannot deallocate page from kernel");
    }
}

int main()
{
    init();
    test();
    return 0;
}

void instantiate_new_family(char *struct_name, uint32_t size)
{
    if (first_container == NULL)
    {
        void *first = get_page_from_kernel(1);
    }
    else
    {
    }
}

///Test module was initialized correctly.
void test()
{
    printf("Page size = %lu\n", SYS_PAGE_SIZE);
    void *address1 = get_page_from_kernel(1);
    void *address2 = get_page_from_kernel(1);
    printf("Page 1 %p | Page 2 %p\n", address1, address2);
    purge_page_from_kernel(address1, 1);
    purge_page_from_kernel(address2, 1);
}