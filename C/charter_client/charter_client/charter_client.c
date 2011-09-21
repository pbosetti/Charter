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

unsigned int charter_deliver_message(struct charter_s *ch, char *msg)
{
  int BASE_PORT = 2000;
  printf("host: %s, id: %d, msg: %s\n", ch->hostname, BASE_PORT + ch->id, msg);
  int sockfd, portno; 
  ssize_t n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  portno = BASE_PORT + ch->id;
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
  return charter_deliver_message(ch, "CLEAR");
}
