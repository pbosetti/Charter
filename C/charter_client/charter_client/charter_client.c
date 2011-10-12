//
//  charter_client.c
//  charter_client
//
//  Created by Paolo Bosetti on 9/21/11.
//  Copyright 2011 Paolo Bosetti. All rights reserved.
//

#include "charter_client.h"

void 
charter_init(struct charter_s *ch)
{
  ch->id = 1;
  ch->hostname = "127.0.0.1";
  ch->delay = CHARTER_DEFAULT_DELAY;
}

enum charter_errors 
charter_deliver_message(const struct charter_s *ch, char *msg)
{
//  printf("host: %s, id: %d, msg: %s\n", ch->hostname, BASE_UDP_PORT + ch->id, msg);
  int sockfd, portno; 
  ssize_t n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  portno = CHARTER_BASE_UDP_PORT + ch->id;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) 
    return SOCKET_ERR;
  
  server = gethostbyname(ch->hostname);
  if (server == NULL)
    return SERVER_ERR;
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    return CONN_ERR;
  
  n = write(sockfd, msg, strlen(msg));
  if (n < 0) 
    return WRITE_ERR;
  
  close(sockfd);
  if (ch->delay > 0)
    usleep(ch->delay);
  return 0;
}

enum charter_errors 
charter_clear(const struct charter_s *ch)
{
  return charter_deliver_message(ch, "CLEAR");
}

enum charter_errors 
charter_close(const struct charter_s *ch)
{
  return charter_deliver_message(ch, "CLOSE");
}

enum charter_errors 
charter_names(const struct charter_s *ch, char **names, const unsigned int count)
{
  char *header = "NAMES ";
  unsigned int i;
  char msg[sizeof(header) + sizeof(names) + count];
  bzero(msg, sizeof(msg));
  strcat(msg, header);
  for (i = 0; i < count; i++) {
    strcat(msg, names[i]);
    strcat(msg, " ");
  }
  return charter_deliver_message(ch, msg);
}

enum charter_errors 
charter_labels(const struct charter_s *ch, char **labels, const unsigned int count)
{
  char *header = "LABELS ";
  unsigned int i;
  char msg[sizeof(header) + sizeof(labels) + count];
  bzero(msg, sizeof(msg));
  strcat(msg, header);
  for (i = 0; i < count; i++) {
    strcat(msg, labels[i]);
    strcat(msg, " ");
  }
  return charter_deliver_message(ch, msg);
}


enum charter_errors 
charter_sary(const struct charter_s *ch, double *ary, const unsigned int count)
{
  char *header = "s ";
  unsigned int i;
  char msg[sizeof(header) + CHARTER_FLOAT_FIELD_SIZE * count];
  bzero(msg, sizeof(msg));
  char field[CHARTER_FLOAT_FIELD_SIZE];
  strcat(msg, header);
  for (i = 0; i < count; i++) {
    sprintf(field, "%f ", ary[i]);
    strcat(msg, field);
  }
  return charter_deliver_message(ch, msg);
}



