
#include "hmac.h"
#include "sha1.h"
#include "md5.h"

#define BLOCK_SIZE 64

void hmac_sha1(const char *text, size_t text_len, const char *key, size_t key_len, void *digest) {
	unsigned char k_ipad[BLOCK_SIZE+1];
	unsigned char k_opad[BLOCK_SIZE+1];
	unsigned char tk[SHA1HashSize];
	if(key_len > BLOCK_SIZE) {
		SHA1Context ctx;
		SHA1Reset(&ctx);
		SHA1Input(&ctx, key, key_len);
		SHA1Result(&ctx, tk);
		key_len = SHA1HashSize;
		key = tk;
	}
	bzero(k_ipad, sizeof(k_ipad));
	bzero(k_opad, sizeof(k_opad));
	bcopy(key, k_ipad, key_len);
	bcopy(key, k_opad, key_len);
	for(int i=0; i<BLOCK_SIZE; i++) {
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}
	SHA1Context context;
	// inner
	SHA1Reset(&context);
	SHA1Input(&context, k_ipad, BLOCK_SIZE);
	SHA1Input(&context, text, text_len);
	SHA1Result(&context, digest);
	// outer
	SHA1Reset(&context);
	SHA1Input(&context, k_opad, BLOCK_SIZE);
	SHA1Input(&context, digest, SHA1HashSize);
	SHA1Result(&context, digest);
	return;
}

void hmac_md5(const char *text, size_t text_len, const char *key, size_t key_len, void *digest) {
	MD5_CTX context;
	unsigned char k_ipad[BLOCK_SIZE+1];
	unsigned char k_opad[BLOCK_SIZE+1];
	unsigned char tk[MD5HashSize];
	if(key_len > BLOCK_SIZE) {
		MD5_CTX tctx;
		MD5Init(&tctx);
		MD5Update(&tctx, key, key_len);
		MD5Final(tk, &tctx);
		key_len = MD5HashSize;
		key = tk;
	}

	// the HMAC_MD5 transform looks like:
	// MD5(K XOR opad, MD5(K XOR ipad, text))
	// where K is an n byte key
	// ipad is the byte 0x36 repeated 64 times
	// opad is the byte 0x5c repeated 64 times
	// and text is the data being protected

	// start out by storing key in pads
	bzero(k_ipad, sizeof(k_ipad));
	bzero(k_opad, sizeof(k_opad));
	bcopy(key, k_ipad, key_len);
	bcopy(key, k_opad, key_len);

	// XOR key with ipad and opad values
	for(int i=0; i<BLOCK_SIZE; i++) {
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}
	// perform inner MD5
	MD5Init(&context);                       // init context for 1st pass
	MD5Update(&context, k_ipad, BLOCK_SIZE); // start with inner pad
	MD5Update(&context, text, text_len);     // then text of datagram
	MD5Final(digest, &context);              // finish up 1st pass
	// perform outer MD5
	MD5Init(&context);                        // init context for 2nd pass
	MD5Update(&context, k_opad, BLOCK_SIZE);  // start with outer pad
	MD5Update(&context, digest, MD5HashSize); // then results of 1st hash
	MD5Final(digest, &context);               // finish up 2nd pass
	return;
}
