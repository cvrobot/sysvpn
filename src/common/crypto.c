#include <sodium.h>

int crypto_init()
{
    sodium_init();
}

void crypto_gen_randombytes(void * const buf, const size_t size);
{
    randombytes_buf(buf, size);
}

int crypto_set_key(struct *crypto c, const unsigned char *pwd, int plen) {
    int ret = 0;
    c->klen = crypto_aead_chacha20poly1305_KEYBYTES;
    c->key = malloc(c->klen);

    ret = crypto_generichash(c->key, c->klen, pwd, plen, NULL, 0);
    if(ret){
        free(c->key);
    }

    return ret;
}

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
