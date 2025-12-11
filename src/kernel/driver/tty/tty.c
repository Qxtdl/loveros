#include <stdint.h>

#include "tty.h"
#include "../../../libc/string.h"
#include "vga.h"
#include "../../arch/i686/asm.h"

size_t terminal_row;
size_t terminal_column;
vga_color_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void tty_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			terminal_buffer[y * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

static inline void terminal_scroll(void) 
{
	memmove(terminal_buffer, terminal_buffer + VGA_WIDTH, (VGA_HEIGHT - 1) * VGA_WIDTH * sizeof(uint16_t));
}

void tty_putchar(char c) 
{
	if (c == '\n') {
		terminal_row++;
		terminal_column = 0;
	}
	else {
		terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = vga_entry(c, terminal_color);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
		}
		if (terminal_row == VGA_HEIGHT) {
			terminal_scroll();
			terminal_row--;
		}
	}
	update_cursor(terminal_column, terminal_row);
}

void tty_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		tty_putchar(data[i]);
}