//
//  charter_client.h
//  charter_client
//
//  Created by Paolo Bosetti on 9/21/11.
//  Copyright 2011 Paolo Bosetti. All rights reserved.
//

struct charter_s {
  unsigned int id;
  char *hostname;
};

unsigned int charter_deliver_message(struct charter_s *ch, char *msg);
unsigned int charter_clear(struct charter_s *ch);
unsigned int charter_close(struct charter_s *ch);
unsigned int charter_names(struct charter_s *ch, char **names, unsigned int count);
