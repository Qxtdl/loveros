#pragma once

#define log(str) printf("[LOG]: " str "\n");
#define vlog(fmt, ...) printf("[LOG]: " fmt "\n", __VA_ARGS__);

int printf(const char* __restrict format, ...);
void puts(const char *str);

