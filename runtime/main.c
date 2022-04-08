
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

  for (int i = 1; i < argc; i += 2) {
	char option = argv[i][1];
	switch (option) {
	  case 'c':
		dct_compress(argv[i + 1], 8, 1);
		break;
	  case 'x':
		dct_expand(argv[i + 1]);
		break;
	  default:
		printf("invalid argument given '-%c'. exiting now...", option);
		exit(1);
	}
  }

  return 0;
}
