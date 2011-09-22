//
//  charter_client.c
//  charter_client
//
//  Created by Paolo Bosetti on 9/21/11.
//  Copyright 2011 Paolo Bosetti. All rights reserved.
//

#include "charter_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <string.h>

unsigned int charter_deliver_message(struct charter_s *ch, char *msg)
{
//  printf("host: %s, id: %d, msg: %s\n", ch->hostname, BASE_UDP_PORT + ch->id, msg);
  int sockfd, portno; 
  ssize_t n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  portno = BASE_UDP_PORT + ch->id;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) 
    return 1;
  
  server = gethostbyname(ch->hostname);
  if (server == NULL)
    return 2;
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    return 3;
  }
  n = write(sockfd, msg, strlen(msg));
  if (n < 0) 
    return 4;
  close(sockfd);
  return 0;
}

unsigned int charter_clear(struct charter_s *ch)
{
  return charter_deliver_message(ch, "CLEAR");
}

unsigned int charter_close(struct charter_s *ch)
{
  return charter_deliver_message(ch, "CLOSE");
}

unsigned int charter_names(struct charter_s *ch, char **names, unsigned int count)
{
  unsigned int i;
  char msg[sizeof(names) + 6 + count];
  bzero(msg, sizeof(msg));
  strcat(msg, "NAMES ");
  for (i = 0; i < count; i++) {
    strcat(msg, names[i]);
    strcat(msg, " ");
  }
  return charter_deliver_message(ch, msg);
}

unsigned int charter_sary(struct charter_s *ch, double *ary, unsigned int count)
{
  unsigned int i;
  char msg[20 * count + 2];
  bzero(msg, sizeof(msg));
  char field[20];
  strcat(msg, "s ");
  for (i = 0; i < count; i++) {
    sprintf(field, "%f ", ary[i]);
    strcat(msg, field);
  }
  return charter_deliver_message(ch, msg);
}



