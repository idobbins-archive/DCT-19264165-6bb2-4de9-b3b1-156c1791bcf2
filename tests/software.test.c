
#include "io.h"
#include "dct.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc != 2) {
	printf("%s\n", "Invalid number of arguments provided. exiting now...");
	exit(1);
  }

  dct_png_t png;

  dct_load_png(argv[1], &png);

  dct_free_png(png);

  return 0;
}