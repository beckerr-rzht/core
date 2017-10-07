#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "net.h"

#define DOVEADM_LOG_CHANNEL_ID 'L'

enum client_connection_type {
	CLIENT_CONNECTION_TYPE_CLI = 0,
	CLIENT_CONNECTION_TYPE_TCP,
	CLIENT_CONNECTION_TYPE_HTTP,
};

struct client_connection {
	pool_t pool;
	enum client_connection_type type;
	const char *name;

	struct ip_addr local_ip, remote_ip;
	in_port_t local_port, remote_port;

	const struct doveadm_settings *set;

	void (*free)(struct client_connection *conn);
};

struct client_connection *
client_connection_tcp_create(int fd, int listen_fd, bool ssl);
struct client_connection *
client_connection_http_create(int fd, bool ssl);

#endif
