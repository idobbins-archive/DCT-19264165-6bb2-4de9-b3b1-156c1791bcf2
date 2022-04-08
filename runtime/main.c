
/*

Discrete Cosine Transform (DCT) Image Compression Tool

Author: Isaac Dobbins

CLI Arguments:

 	compress (-c)
 		Image to be compressed.

	degree (-d)
 		Desired degree of the DCT matrix to be used. Takes the form n x n where n is the
		magnitude of each dimension.

	p-value (-p)
 		Desired p-value used to initialize the quantization matrix.

*/

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
  const char *file = argv[2];
  int d = atoi(argv[4]);
  float p = atof(argv[6]);

  dct_compress(file, d, p);

  return 0;
}
