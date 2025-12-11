#include "gdt.h"

extern void load_gdt(gdt_desc_t *desc);

gdt_t gdt = {
    .null           = {0xFFFF, 0, 0, 0x00, 0x00, 0},
    .kernel_code    = {0xFFFF, 0, 0, 0x9a, 0xcf, 0},
    .kernel_data    = {0xFFFF, 0, 0, 0x92, 0xcf, 0},
    .user_null      = {0xFFFF, 0, 0, 0x00, 0x00, 0},
    .user_code      = {0xFFFF, 0, 0, 0x9a, 0xcf, 0},
    .user_data      = {0xFFFF, 0, 0, 0x92, 0xcf, 0},
};

void initalize_gdt(void)
{
    gdt_desc_t desc = {sizeof(gdt_t) - 1, (uint64_t)&gdt};
    load_gdt(&desc);
}

void print_gdt(void)
{
    asm volatile("");
}