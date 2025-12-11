#include <stddef.h>
#include <stdint.h>

#include "../libc/stdio.h"

extern char _kernel_end[];

static uintptr_t alloc_ptr = (uintptr_t)_kernel_end + 16;

void *malloc(size_t size) 
{
    alloc_ptr = alloc_ptr & 0xFFFFFF0;
    uintptr_t res = alloc_ptr;
    alloc_ptr += 16;
    return (void *)res;
}

void free(void *blk)
{
    log("free: STUB")
}