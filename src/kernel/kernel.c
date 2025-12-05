#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "arch/i686/tty.h"
#include "../libc/stdio.h"
#include "abort.h"

void kernel_main(void) 
{
	tty_initialize();
	log("Welcome to Loveros OS!");
}