//
//  charter_client.h
//  charter_client
//
//  Created by Paolo Bosetti on 9/21/11.
//  Copyright 2011 Paolo Bosetti. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <string.h>
#include <unistd.h>

#define CHARTER_BASE_UDP_PORT 2000
#define CHARTER_DEFAULT_DELAY 10000
#define CHARTER_FLOAT_FIELD_SIZE 20

enum charter_errors {
  SOCKET_ERR = 1,
  SERVER_ERR = 2,
  CONN_ERR   = 3,
  WRITE_ERR  = 4
  };

struct charter_s {
  unsigned int id;
  char *hostname;
  useconds_t delay;
};

void charter_init(struct charter_s *ch);
enum charter_errors charter_deliver_message(const struct charter_s *ch, char *msg);
enum charter_errors charter_clear(const struct charter_s *ch);
enum charter_errors charter_close(const struct charter_s *ch);
enum charter_errors charter_names(const struct charter_s *ch, char **names, const unsigned int count);
enum charter_errors charter_labels(const struct charter_s *ch, char **labels, const unsigned int count);
enum charter_errors charter_sary(const struct charter_s *ch, double *ary, const unsigned int count);
