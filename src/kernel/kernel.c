#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "driver/tty/tty.h"
#include "../libc/stdio.h"
#include "../libc/alloc.h"
#include "arch/i686/asm.h"
#include "arch/i686/gdt/gdt.h"
#include "abort.h"

void kernel_main(void) 
{
	initalize_gdt();
	tty_initialize();
	log("GDT INIT... OK")
	log("Welcome to Loveros OS!")
}