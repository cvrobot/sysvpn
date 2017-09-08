#include <stdio.h>


process_login(struct sysvpn_srv *srv, char *buf, int len)
{
    struct auth a;
    struct crypto *cry;

    if(auth_unpack(&a, *data, len)){
        //TODO: unpack fail, add debug info
        return -1;
    }
    
    //get session from login hash table according to ip address
    if(s == NULL){
        //check ip not locked or lock time > 15m, unlock it.
        
        //get new session from list or create new session if no init state session , and send server side (chm + EXG_KEY) + (chm + ken len) + SRV key
        s->state = SESSION_EXG_INIT;
        //put key to 
    }

    cry = s->c;
    switch(s->state){
        case SESSION_INIT:
        case SESSION_EXG_KEY:
            if(req_type == EXG_KEY){//client may not got key, resend it only x times.
                if( sizeof(s->key)/2 != a.mlen){
                    //crack?
                    return;
                }
                memcpy(s->key + sizeof(s->key)/2, a.msg, sizeof(s->key)/2);
 
                crypto_gen_randombytes(s->key, sizeof(s->key)/2);
                //regen server key, and send server side (chm + SESSION_EXG_KEY) generated half key
                if(s->cnt <= srv->retry){
				    s->cnt++;
                }else{
                    //do nothing, may lock ip for 15m(add ip to lock list).
                }
            }else if(req_type == SESSION_LOGIN){
                crypto_set_key(cry, s->key, sizeof(s->key));
                cry->c = a.m;
                cry->clen = a.mlen;
                if(crypto_decrypt(cry)){
                    //decrypt fail
                    return;
                }
                if(check_token_valid(cry->m, cry->len)){
                    a.req_type = REQ_INV_KEY;
                    session_reply();//
                    return;
                }
                //if session count to a client is less 3 oK, otherwise reply too many device logined.
                //if valid save token
                s->state = SESSION_LOGIN;
                //alloc server ip, port for tcp?
            }
            break;
        case SESSION_LOGIN:
            //send log out info to client process.
    }
}
}

process_tun()
{
    //get session connect,disconnect ,connect timeout info from tun process
}

handle_client(sysvpn_srv *srv)
{
	int retry = 3;
	enum request_type req_type;
    while(src->runing){
        //wait client, wait tun
        process_login(srv, data, len);
        //process_();//recv connect info from tun process
    }
}

/*
    ret=pthread_create(&id_1,NULL,(void  *) thread_1,NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
    return -1;  
*/
srv_run(vpn *v)
{
    pid_t pid = fork();
    if (pid == -1) {
        err("fork");
        return -1;
    }
    if (pid > 0) {
        // sleep 0.05s, wait tun up?
        usleep(50000);
        handle_client();//maintain client info
    }else{
        vpn_up();// tun
        handle_data();//process client data receive&send, feedback client connect info
        vpn_down();
    }
}

vpn_init(vpn *v)
{
	v->tun = open_tun();

}

int main(int argc, char** argv){

	 parse_args(argc, argv);
	 
	 vpn_init();//create socket
	 
	 srv_run();
     return 0;
}
