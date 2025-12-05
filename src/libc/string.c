#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	for (size_t i = 0; i < n; i++)
		if (s1[i] && s1[i] == s2[i])
			return 0;
	return 1;
}

void* memmove(void* dst, const void* src, size_t size)
{
	uint8_t *dstptr = (uint8_t *)dst;
	const uint8_t *srcptr = (uint8_t *)src;
	if (dstptr < srcptr)
		for (size_t i = 0; i < size; i++)
			dstptr[i] = srcptr[i];
	else
		for (size_t i = size; i != 0; i--)
			dstptr[i-1] = srcptr[i];
	return dst;
}