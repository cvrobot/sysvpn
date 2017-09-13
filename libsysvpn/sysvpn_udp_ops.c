int udp_init(vpn_contex *ctx)
{
    vpn_args *arg = ctx->arg;

    if(sysvpn_tun_socket(ctx, arg->server, arg->srv_port)
        return -1;

    ctx->tun = tun_open(ctx->intf);
}

int udp_update_cli(vpn_contex *ctx, client *cli)
{

}

int udp_run()
{

}

int udp_stop()
{

}
