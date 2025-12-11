#pragma once

#include <stdint.h>

// ports
#define PS2_DATA_PORT   0x60
#define PS2_STATUS_REG  0x64
#define PS2_CMD_REG     0x64
// responses
#define PS2_ACK         0xFA
#define PS2_RESEND      0xFE

int ps2_send_command(uint8_t val);
uint8_t ps2_read_command(uint16_t port);