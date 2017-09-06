#include <stdio.h>
#include <sodium.h>

#define MESSAGE_LEN 163
unsigned char nonce[crypto_aead_chacha20poly1305_NPUBBYTES];
unsigned char key[crypto_aead_chacha20poly1305_KEYBYTES];
unsigned char ciphertext[163 + crypto_aead_chacha20poly1305_ABYTES];
unsigned long long ciphertext_len = 0;
unsigned char MESSAGE[MESSAGE_LEN] = {0};

unsigned char decrypted[MESSAGE_LEN] = {1};
unsigned long long decrypted_len;

#define ADDITIONAL_DATA (const unsigned char *) "123456"
#define ADDITIONAL_DATA_LEN 6

msg_print(char *data, int len)
{
    int i;
    for (i = 0; i < len; ++i) {
        printf(",0x%02x", (unsigned int)data[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\n");
}
int main(int argc, char** argv){

    memset(MESSAGE, 1, MESSAGE_LEN);
    memset(decrypted, 0, MESSAGE_LEN);
    if (sodium_init() == -1) {
        return 1;
    }
    msg_print(MESSAGE, MESSAGE_LEN);
    //msg_print(decrypted, MESSAGE_LEN);
    printf("\n");printf("\n");
    //randombytes_buf(key, sizeof(key));
    randombytes_buf(nonce, sizeof(nonce));
    msg_print(nonce, sizeof(nonce));
    crypto_aead_chacha20poly1305_encrypt(ciphertext, &ciphertext_len,
                                     MESSAGE, MESSAGE_LEN,
                                     ADDITIONAL_DATA, ADDITIONAL_DATA_LEN,
                                     NULL, nonce, key);
    //msg_print(MESSAGE, MESSAGE_LEN);
    msg_print(ciphertext, MESSAGE_LEN);
    printf("ciphertext_len:%d\n",ciphertext_len);printf("\n");

    crypto_aead_chacha20poly1305_decrypt(decrypted, &decrypted_len,
                                         NULL,
                                         ciphertext, ciphertext_len,
                                         ADDITIONAL_DATA,
                                         ADDITIONAL_DATA_LEN,
                                        nonce, key);
    //msg_print(MESSAGE, MESSAGE_LEN);
    msg_print(decrypted, MESSAGE_LEN);
    return 0;
}