typedef enum{
    SYSVPN_CLI,
    SYSVPN_SRV,
}sysvpn_mode;

typedef struct{
    unsigned char *pwd;
    int pwd_len;
    uint32_t input_tun_ip;
}client;

void *sysvpn_init(enum sysvpn_mode,  const char *server  uint16_t port);
sysvpn_set_debug(void* vpn, int level);
sysvpn_start(void *vpn);
sysvpn_stop(void *vpn);
