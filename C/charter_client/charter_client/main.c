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
#include <unistd.h>

typedef char * string;

int main (int argc, const char * argv[])
{
  struct charter_s ch;
  unsigned int i;
  double ary[3];
  string names[2];
  
  ch.id = 1;
  ch.hostname = "127.0.0.1";
  charter_clear(&ch);
  
  for (i = 0; i < 200; i++) {
    ary[0] = i/10.0;
    ary[1] = sin(i / 10.0);
    ary[2] = cos(i / 10.0);
    charter_sary(&ch, ary, 3);
//    usleep(10000);
  }
  names[0] = "Sin";
  names[1] = "Cos";
  
  charter_names(&ch, names, 2);
  //charter_close(&ch);
  return 0;
}

