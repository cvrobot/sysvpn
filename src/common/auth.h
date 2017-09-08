
enum request_type{
    REQ_EXG_KEY,
    REQ_INV_KEY,//key invalid
    REQ_LOG_IN,
    REQ_CON_ED,
    REQ_CON_TIMOUT,
    REQ_CON_DIS,
    REQ_LOG_OUT,
};

struct auth{
	enum request_type req_type;
	unsigned char chm;
	char *m;
	int mlen;
};

int auth_unpack(struct auth *a, unsigned char *data, int len);
int auth_pack(struct auth *a, unsigned char *data, int *len);
