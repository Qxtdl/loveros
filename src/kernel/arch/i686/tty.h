#pragma once

#include <stddef.h>
#include <stdint.h>

void tty_initialize(void);
void tty_setcolor(uint8_t color);
void tty_putentryat(char c, uint8_t color, size_t x, size_t y);
void tty_putchar(char c);
void tty_write(const char* data, size_t size);
