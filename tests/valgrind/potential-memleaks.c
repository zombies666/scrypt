#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/aes.h>

#define KEYLEN 128

/* Keep all code in `int main` to simplify the valgrind suppression. */
int
main()
{

	/* Problem with FreeBSD fgets() with stdin. */
	{
		char buf[8];

		if (fgets(buf, 8, stdin) == NULL)
			goto err0;
	}

	/* OpenSSL library memleak on Ubuntu 16.04. */
	{
		AES_KEY kexp_openssl;
		uint8_t key[KEYLEN];

		memset(key, 0, KEYLEN);
		AES_set_encrypt_key(key, KEYLEN, &kexp_openssl);
	}

	/* Success! */
	exit(0);

err0:
	/* Failure! */
	exit(1);
}
