#include <stdio.h>

int main(int argc, char** argv){
     printf("%s", "Hello, Linux World!\n");
	 parse_args(argc, argv);
	 
	 srv_init();//create socket
	 
	 while(1){
		 
	 }
     return 0;
}

sysvpn_srv *srv_init()
{
	srv->tun = open_tun();
}

conn_rcv()
{
//wait  data from conn socket,wait control info from control socket

//recv datarecvfrom();
dispatch_data();

}

dispatch_data(sysvpn_srv *srv, char *data)
{
	int retry = 3;
	enum request_type req_type;
    //get session from hash table according to ip address
    if(s == NULL){
        //check ip not locked or lock time > 15m, unlock it.
        //check data len match (chm + EXG_KEY) + (chm + key len) + CLI key
        //get new session from list or create new session if no init state session , and send server side (chm + EXG_KEY) + (chm + ken len) + SRV key
        s->state = SESSION_EXG_KEY;
        //put key to 
    }else{
        switch(s->state){
            case SESSION_EXG_KEY:
                if(req_type == EXG_KEY){//client not got key, resend it only 3 times.
                    //regen server key, and send server side (chm + SESSION_EXG_KEY) generated half key
                    if(s->cnt <= retry){
						s->cnt++;
                        //do nothing, may lock ip for 15m(add ip to lock list).
                    }
                }else if(req_type == SESSION_LOGIN){
                    //use session key to decrypto token, then check token valid
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
