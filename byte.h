
#ifndef _BYTE_H_
#define _BYTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// string to byte array
void* atob(size_t *size, const char *str);

// byte array to string
char* btoa(void *bytes, size_t size);

size_t padblk(void **data, char byte, size_t size, size_t blocksize);

void bcopy(const void *src, void *dst, size_t len);
void bzero(void *s, size_t n);

#endif
