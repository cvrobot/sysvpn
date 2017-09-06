#include <sodium.h>

int crypto_init
int crypto_encryp(unsigned char *c, const unsigned char *m, unsigned long long mlen)
{
	char *nonce = c;
	int nlen = crypto_aead_chacha20poly1305_NPUBBYTES;
	randombytes_buf(nonce, nlen);
    return crypto_aead_chacha20poly1305_encrypt(c + noncecrypto_aead_chacha20poly1305_NPUBBYTES, &ciphertext_len,
                                     m, mlen,
                                     NULL, 0,
                                     NULL, nonce, key);
}

int crypto_decryp(unsigned char *m, const unsigned char *c, unsigned long long clen)
{
	char *nonce = c;
	int nlen = crypto_aead_chacha20poly1305_NPUBBYTES;
    return crypto_aead_chacha20poly1305_decrypt(m, &mlen,
                                         NULL,
                                         c +, clen,
                                         NULL,
                                         0,
                                        nonce, key);
}