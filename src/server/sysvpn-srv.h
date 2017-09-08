#define SYSVPN_KEY_LEN 16

enum state{
    SESSION_INIT,
    SESSION_EXG_KEY,
    SESSION_LOGIN,
    SESSION_CONNECT,
};

struct session{
    char key[SYSVPN_KEY_LEN];	//save keys
    int cnt;					//exchange key retry count
    enum state st;
    struct crypto c;
};

struct config{
    
}

struct sysvpn_srv{
    
    
    
};

//session protocol
//(chm + request type) + (chm + datalen) + data
session_init(session *s);
session_process

wait_se(struct sysvpn_srv *srv);
