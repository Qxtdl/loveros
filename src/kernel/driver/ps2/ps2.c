#include <stdint.h>

#include "ps2.h"
#include "../../arch/i686/asm.h"
#include "../../../libc/stdio.h"

int ps2_send_command(uint8_t val)
{
    while (inb(PS2_STATUS_REG) & 0x2); // wait till its not full
    outb(PS2_DATA_PORT, val);

    while (1) {
        uint8_t reply = ps2_read_command(PS2_DATA_PORT);

        if (reply == PS2_ACK) break;
        else if (reply == PS2_RESEND) {
            while (inb(PS2_STATUS_REG) & 0x2);
            outb(PS2_DATA_PORT, val);
        }
        else {
            vlog("PS/2 Controller Error, got %x", reply)
            return 0;
        }
    }

    return 1;
}

uint8_t ps2_read_command(uint16_t port)
{
    while (!(inb(PS2_STATUS_REG) & 0x1));
    return inb(PS2_DATA_PORT);
}