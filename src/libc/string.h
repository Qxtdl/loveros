#pragma once

#include <stddef.h>

size_t strlen(const char* str);
int strncmp(const char *s1, const char *s2, size_t n);
void* memmove(void* dst, const void* src, size_t size);