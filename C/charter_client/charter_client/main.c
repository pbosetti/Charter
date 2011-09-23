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
  struct charter_s ch; // Declare the charter
  unsigned int i;
  double ary[3];
  string names[2];
  
  charter_init(&ch);  // Initialize defaukt values: ID = 1, host = localhost, delay = 10000 us
  ch.delay = 50000;   // Override default delay to 50000 us
  charter_clear(&ch); // Clear App buffer
  
  for (i = 0; i < 200; i++) {
    ary[0] = i/10.0;
    ary[1] = sin(i / 10.0);
    ary[2] = cos(i / 10.0);
    charter_sary(&ch, ary, 3); // Send data
  }
  
  names[0] = "Sin";
  names[1] = "Cos";
  charter_names(&ch, names, 2); // Set series names
  
  //charter_close(&ch);         // If needed you can close the connection
  return 0;
}

