#ifndef __CLIENT_H
#define __CLIENT_H

#include "network.h"
#include "master.h"
#include "client-common.h"

struct imap_client {
	struct client common;

	time_t created;
	int refcount;

	struct io *io;
	struct istream *input;
	struct ostream *output;
	struct imap_parser *parser;

	time_t last_input;
	unsigned int bad_counter;

	const char *cmd_tag, *cmd_name;

	unsigned int cmd_finished:1;
	unsigned int skip_line:1;
	unsigned int input_blocked:1;
	unsigned int destroyed:1;
};

void client_destroy(struct imap_client *client, const char *reason);

void client_send_line(struct imap_client *client, const char *line);
void client_send_tagline(struct imap_client *client, const char *line);

int client_read(struct imap_client *client);
void client_input(void *context);

void client_ref(struct imap_client *client);
int client_unref(struct imap_client *client);

void clients_init(void);
void clients_deinit(void);

#endif
