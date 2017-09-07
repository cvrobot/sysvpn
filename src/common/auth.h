struct auth{
	enum request_type req_type;
	unsigned char chm;
	char *m;
	int mlen;
};
int auth_unpack(struct auth *a, unsigned char *data, int len);
int auth_pack(struct auth *a, unsigned char *data, int *len);