#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "stdio.h"
#include "string.h"
#include "../kernel/driver/tty/tty.h"

int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	while (*format != '\0') {
		if (*format != '%')
			tty_putchar(*format);
		else {
			// this char is format specifier
			const char *format_specifier = format + 1;

			if (!strncmp(format_specifier, "s", 1)) {
				format = format_specifier;
				const char *str = va_arg(parameters, const char *);
				tty_write(str, strlen(str));
			}
			if (!strncmp(format_specifier, "c", 1)) {
				format = format_specifier;
				const char ch = (char)va_arg(parameters, int);
				tty_putchar(ch);
			}
			if (!strncmp(format_specifier, "x", 1)) {
				format = format_specifier;
				printf("$");
				
				const char hex_digits[] = "0123456789abcdef";
				char buf[8 + 1];
				buf[8] = '\0';

				int i = 8;
				uint32_t n = va_arg(parameters, uint32_t);

				for (int i = 0; i < 8; i++) {
					uint8_t digit = (n >> (7 - i) * 4) & 0xF;
					// if (digit < 10) {
					// 	tty_putchar(digit | 0x20);
					// } else tty_putchar(digit | 0x40);
					switch (digit) {
						case 0x0: tty_putchar('0'); break;
						case 0x1: tty_putchar('1'); break;
						case 0x2: tty_putchar('2'); break;
						case 0x3: tty_putchar('3'); break;
						case 0x4: tty_putchar('4'); break;
						case 0x5: tty_putchar('5'); break;
						case 0x6: tty_putchar('6'); break;
						case 0x7: tty_putchar('7'); break;
						case 0x8: tty_putchar('8'); break;
						case 0x9: tty_putchar('9'); break;
						case 0xA: tty_putchar('A'); break;
						case 0xB: tty_putchar('B'); break;
						case 0xC: tty_putchar('C'); break;
						case 0xD: tty_putchar('D'); break;
						case 0xE: tty_putchar('E'); break;
						case 0xF: tty_putchar('F'); break;
					}
				}
			}
		}
		format++;
	}

	return 0; // no error
}

inline void puts(const char *str)
{
	printf("%s\n", str);
}
