
#include "../include/dct.h"

#include "actions.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {

  if (argc <= 1) {
	printf("no arguments found. exiting now...");
	exit(1);
  }

  else if ((argc - 1) % 2 != 0) {
	printf("incorrect number of arguments given. exiting now...");
	exit(1);
  }

  // argument structure is purposefully rigid
  const char* file = argv[2];
  int d = atoi(argv[4]);
  float p = atof(argv[6]);

  dct_compress(file, d, p);

  return 0;
}
