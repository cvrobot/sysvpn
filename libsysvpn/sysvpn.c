typedef struct {
    sysvpn_mode mode;
    struct sockaddr_storage srv_addr;
    struct sockaddr *srv_addrp;
    socklen_t srv_addrlen;
    int is_tcp;
    vpn_ops *ops;
}sysvpn_contex;

int vpn_sock_addr(const char *server  uint16_t port,struct sockaddr *addr, socklen_t* addrlen int is_tcp)
{
    struct addrinfo hints;
    struct addrinfo *res;
    int ret;

    memset(&hints, 0, sizeof(hints));
    if(is_tcp){
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_TCP;
    }else{
      hints.ai_socktype = SOCK_DGRAM;
      hints.ai_protocol = IPPROTO_UDP;
    }

    ret = getaddrinfo(host, NULL, &hints, &res);
    if (0 != ret) {
        errf("getaddrinfo: %s", gai_strerror(ret));
        return -1;
    }

    if (res->ai_family == AF_INET)
        ((struct sockaddr_in *)res->ai_addr)->sin_port = htons(port);
    else if (res->ai_family == AF_INET6)
        ((struct sockaddr_in6 *)res->ai_addr)->sin6_port = htons(port);
    else {
        errf("unknown ai_family %d", res->ai_family);
        freeaddrinfo(res);
        return -1;
    }
    memcpy(addr, res->ai_addr, res->ai_addrlen);
    *addrlen = res->ai_addrlen;

    return 0;
}

sysvpn_socket_creat(const char *server, uint16_t port)
{
    
    vpn_sock_addr(const char *server, uint16_t port, ctx->srv_addrp, ctx->srv_addrlen, ctx->is_tcp);
}

void *sysvpn_init(enum sysvpn_mode,  const char *server  uint16_t port)
{
    vpn_contex* ctx = malloc(sizeof(vpn_contex));

    memset(ctx, 0 , sizeof(vpn_contex));
    ctx->mode = sysvpn_mode;
    ctx->srv_addrp = (struct sockaddr *)&ctx->srv_addr;
    ctx->is_tcp = 1;
    

    vpn_debug_init();
    return (void *)ctx; 
}

sysvpn_set_callback(void *vpn, vpn_ops *ops)
{
    vpn_contex* ctx = (vpn_contex*)vpn;
    ctx->ops = ops;
}

sysvpn_set_debug(void *vpn, char * file, int level)
{

}

vpn_update_cli(void *vpn, client *cli)
{
    vpn_contex* ctx = (vpn_contex*)vpn;
}

sysvpn_start(void *vpn)
{
    vpn_contex* ctx = (vpn_contex*)vpn;
    ctx->tun = tun_open(ctx->intf);
    vpn_tun
}

sysvpn_stop();
sysvpn_deinit(void *vpn);
