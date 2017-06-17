
#include "main.h"
#include "byte.h"
#include "hmac.h"

int main(int argc, char **argv) {
	const char *key = "1234";
	const char *msg = "my name is mert";
	void *bytes[SHA1HashSize];
	hmac_sha1(msg, strlen(msg), key, strlen(key), bytes);
	printf("%s\n", btoa(bytes, SHA1HashSize));
	return 0;
}
