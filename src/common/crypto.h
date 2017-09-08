struct crypto{
    unsigned char *m;
    unsigned long long *mlen;
    unsigned char *c;
    unsigned long long *clen;
    const unsigned char *ad,
    unsigned long long adlen,
    const unsigned char *npub;
    unsigned int nlen;
    unsigned char *k;
    unsigned int klen;
};
