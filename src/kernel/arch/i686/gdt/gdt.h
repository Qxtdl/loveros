#pragma once

#include <stdint.h>

typedef struct {
    uint16_t size;
    uintptr_t offset;
} __attribute((packed)) gdt_desc_t;

typedef struct {
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t limit1_flags;
    uint8_t base2;
} __attribute((packed)) gdt_entry_t;

typedef struct {
    gdt_entry_t null;
    gdt_entry_t kernel_code;
    gdt_entry_t kernel_data;
    gdt_entry_t user_null;
    gdt_entry_t user_code;
    gdt_entry_t user_data;
} __attribute__((packed)) gdt_t;

void initalize_gdt(void);