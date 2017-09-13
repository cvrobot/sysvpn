#include "log.h"
#include "crypto.h"

typedef struct {
    int domain;
    struct sockaddr_storage srv_addr;
    struct sockaddr *srv_addrp;
    socklen_t srv_addrlen;
    FILE *log_fp;
    vpn_ops *ops;
    vpn_args *arg;
}sysvpn_contex;

int vpn_addr_info(const char *server  uint16_t port, struct sockaddr *addr, socklen_t* addrlen, int *domain, int is_tcp)
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
        log_error("getaddrinfo: %s", gai_strerror(ret));
        return -1;
    }

    if (res->ai_family == AF_INET)
        ((struct sockaddr_in *)res->ai_addr)->sin_port = htons(port);
    else if (res->ai_family == AF_INET6)
        ((struct sockaddr_in6 *)res->ai_addr)->sin6_port = htons(port);
    else {
        log_error("unknown ai_family %d", res->ai_family);
        freeaddrinfo(res);
        return -1;
    }

    memcpy(addr, res->ai_addr, res->ai_addrlen);
    *addrlen = res->ai_addrlen;
    *domain = res->ai_family;
    freeaddrinfo(res);

    return 0;
}

int vpn_creat_sock(int domain, const struct sockaddr *addr,
                socklen_t addrlen, int is_tcp)
{
    int sock;
    int type,protocol;

    if(is_tcp){
        type = SOCK_STREAM;
        protocol = IPPROTO_TCP;
    }else{
        type = SOCK_DGRAM;
        protocol = IPPROTO_UDP;
    }

    sock = socket(domain, type, protocol);
    if (-1 == sock ) {
        log_error("can not create socket");
        return -1;
    }

    if (addr != NULL) {
        if (0 != bind(sock, addr, addrlen)) {
            log_error("can not bind %s:%d", host, port);
            close(sock);
            return -1;
        }
    }

    flags = fcntl(sock, F_GETFL, 0);
    if (flags != -1) {
        if (-1 != fcntl(sock, F_SETFL, flags | O_NONBLOCK))
            return sock;
    }
    log_error("fcntl");

    close(sock);
    return -1;
}

int sysvpn_tun_socket(vpn_contex* ctx, const char *server, uint16_t port)
{
    int ret = 0;
    ret = vpn_addr_info(server, port, ctx->srv_addrp, &ctx->srv_addrlen, &ctx->domain, ctx->arg->is_tcp);
    if(ret)
        return ret;
    ctx->sock = vpn_creat_sock(ctx->domain, ctx->srv_addrp, ctx->srv_addrlen, ctx->arg->is_tcp);
    return ctx->sock;
}

static void vpn_debug_init(vpn_contex* ctx, char * file, int level)
{
    if(file != NULL){
        ctx->log_fp = fopen(file,"w+");
        if(ctx->log_fp != NULL)
            log_set_fp(ctx->log_fp);
    }
    log_set_level(level);
}

static void vpn_debug_deinit(vpn_contex* ctx)
{
    if(ctx->log_fp != NULL)
        fclose(ctx->log_fp);
}

static int vpn_chk_args(vpn_args *arg)
{
    if(arg->is_tcp){
        log_error("not support TCP mode");
        return -1;
    }
    return 0;
}

static void vpn_set_ops(vpn_contex *ctx)
{
    if(ctx->arg->istcp)
        ctx->ops = tcp_ops;
    else
        ctx->ops = udp_ops;
}

void *sysvpn_init(vpn_args *arg)
{
    vpn_contex* ctx = malloc(sizeof(vpn_contex) + sizeof(vpn_args));

    memset(ctx, 0 , sizeof(vpn_contex));
    ctx->arg = (vpn_args *arg)((void*)ctx + sizeof(vpn_contex));
    memcpy(ctx->arg, arg, sizeof(vpn_args));

    ctx->srv_addrp = (struct sockaddr *)&ctx->srv_addr;

    if(vpn_check_args(arg))
        return -1;

    vpn_debug_init(arg->logfile, arg->level);

    crypto_init();

    vpn_set_ops(ctx);

    ctx->ops->init(ctx);

    return (void *)ctx; 
}

int vpn_update_cli(void *vpn, client *cli)
{
    vpn_contex* ctx = (vpn_contex*)vpn;
    return ctx->ops->update_cli(ctx, cli);
}

sysvpn_start(void *vpn)
{
    vpn_contex *ctx = (vpn_contex*)vpn;
    tun_up(ctx);
    ctx->ops->run(ctx, cli);
    tun_down(ctx);
}

sysvpn_stop(void *vpn)
{
    vpn_contex *ctx = (vpn_contex*)vpn;
    return ctx->ops->stop(ctx, cli);
}

sysvpn_deinit(void *vpn)
{
    vpn_contex *ctx = (vpn_contex*)vpn;

    vpn_debug_deinit(ctx);
    free(ctx);
}
