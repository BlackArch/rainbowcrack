/*
   RainbowCrack - a general propose implementation of Philippe Oechslin's faster time-memory trade-off technique.

   Copyright (C) Zhu Shuanglei <shuanglei@hotmail.com>
*/

#include "HashAlgorithm.h"

#include <openssl/des.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#ifdef _WIN32
	#pragma comment(lib, "libeay32.lib")
#endif

void setup_des_key(unsigned char key_56[], des_key_schedule &ks)
{
	des_cblock key;

	key[0] = key_56[0];
	key[1] = (key_56[0] << 7) | (key_56[1] >> 1);
	key[2] = (key_56[1] << 6) | (key_56[2] >> 2);
	key[3] = (key_56[2] << 5) | (key_56[3] >> 3);
	key[4] = (key_56[3] << 4) | (key_56[4] >> 4);
	key[5] = (key_56[4] << 3) | (key_56[5] >> 5);
	key[6] = (key_56[5] << 2) | (key_56[6] >> 6);
	key[7] = (key_56[6] << 1);

	//des_set_odd_parity(&key);
	des_set_key(&key, ks);
}

void HashLM(unsigned char* pPlain, int nPlainLen, unsigned char* pHash)
{
	/*
	unsigned char data[7] = {0};
	memcpy(data, pPlain, nPlainLen > 7 ? 7 : nPlainLen);
	*/

	int i;
	for (i = nPlainLen; i < 7; i++)
		pPlain[i] = 0;

	static unsigned char magic[] = {0x4B, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25};
	des_key_schedule ks;
	//setup_des_key(data, ks);
	setup_des_key(pPlain, ks);
	des_ecb_encrypt((des_cblock*)magic, (des_cblock*)pHash, ks, DES_ENCRYPT);
}

void HashMD5(unsigned char* pPlain, int nPlainLen, unsigned char* pHash)
{
	MD5(pPlain, nPlainLen, pHash);
}

void HashSHA1(unsigned char* pPlain, int nPlainLen, unsigned char* pHash)
{
	SHA1(pPlain, nPlainLen, pHash);
}
