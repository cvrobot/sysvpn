
int auth_unpack(struct auth *a, unsigned char *data, int len)
{
	int i = 0;
	for(i=2; i < len,i++)
		a->chm += data[i];
	a->req_type = data[0] - a->chm;
	a->mlen = data[1] - a->chm;
	a->m = data + 2;
	
	if(a->mlen == len - 2)
		return 0;

	return -1;
}

int auth_pack(struct auth *a, unsigned char *data, int *len)
{
	int i = 0;
	unsigned char chm = 0;
	if(*len < a->mlen)
		return -1;

	data[0] = (unsigned char)auth->req_type;
	data[1] = a->mlen;
	for(i=0; i < a->mlen,i++)
		chm += a->m[i];

	data[0] += chm;
	data[1] += chm;
	memcpy(data + 2,a->m, a->mlen);
	
	return 0;
}