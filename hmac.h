
#ifndef _HMAC_H_
#define _HMAC_H_

#include <stdint.h>
#include <stdlib.h>

#define MD5HashSize 16

// redis sha1: http://download.redis.io/redis-stable/src/sha1.c

void hmac_sha1(const char *text, size_t text_len, const char *key, size_t key_len, void *digest);

void hmac_md5(const char *text, size_t text_len, const char *key, size_t key_len, void *digest);

#endif
