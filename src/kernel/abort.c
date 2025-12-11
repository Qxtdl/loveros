#include "../libc/stdio.h"

__attribute__((__noreturn__))
void _abort(const char *reasson) {
    printf("Kernel Panic: %s\n", reasson);
    asm volatile("hlt");
    while (1);
    __builtin_unreachable();
}