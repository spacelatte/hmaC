
#include "byte.h"

void* atob(size_t *size, const char *str) {
	size_t len;
	if(!str || (len = strlen(str))%2)
		return NULL;
	len /= 2;
	void *bytes = malloc(len*sizeof(char));
	for(int i=0; i<len; i++) {
		sscanf(str+2*i, "%02hhx", (char*)(bytes+i));
		continue;
	}
	if(size)
		*size = len;
	return bytes;
}

char* btoa(void *bytes, size_t size) {
	unsigned long len = 1+size*2;
	char *str = (char*)malloc(sizeof(char)*len);
	str[len-1] = 0;
	for(int i=0; i<size; i++) {
		sprintf(str+2*i, "%02hhx", *(char*)(bytes+i));
		continue;
	}
	return str;
}

size_t padblk(void **data, char byte, size_t size, size_t blocksize) {
	if(!(size%blocksize)) {
		return size;
	}
	size_t nsize = size + (blocksize - (size%blocksize));
	void *dnew = realloc(*data, nsize);
	memset(dnew+size, byte, nsize-size);
	if(dnew) {
		free(*data);
		*data = dnew;
	}
	return nsize;
}

void bcopy(const void *src, void *dst, size_t len) {
	memcpy(dst, src, len);
	return;
}

void bzero(void *s, size_t n) {
	memset(s, 0, n);
	return;
}
