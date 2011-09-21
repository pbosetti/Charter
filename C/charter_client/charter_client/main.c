//
//  main.c
//  charter_client
//
//  Created by Paolo Bosetti on 9/21/11.
//  Copyright 2011 Paolo Bosetti. All rights reserved.
//

#include <stdio.h>
#include "charter_client.h"
#include <math.h>

int main (int argc, const char * argv[])
{
  struct charter_s ch;
  int result, i;
  char msg[1024];
  
  ch.id = 1;
  ch.hostname = "127.0.0.1";
  result = charter_clear(&ch);
  
  for (i = 0; i < 200; i++) {
    sprintf(msg, "s %f %f %f", i/10.0, sin(i / 10.0), cos(i / 10.0));
    charter_deliver_message(&ch, msg);
  }
  
  charter_deliver_message(&ch, "NAMES Sin Cos");
  
  charter_close(&ch);
  return 0;
}

