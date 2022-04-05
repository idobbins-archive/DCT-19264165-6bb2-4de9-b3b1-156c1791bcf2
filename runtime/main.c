
#include "../include/dct.h"

#include "compute.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  if (argc != 2) {
	printf("%s\n", "Invalid number of arguments provided. exiting now...");
	exit(1);
  }

  dct_source_t kernel_source;
  dct_load_file(argv[1], &kernel_source);

  dct_compute_t compute;
  dct_init_compute(&compute);

  int *a = (int *)compute.buffers[0];
  int *b = (int *)compute.buffers[1];
  int *r = (int *)compute.buffers[2];

  srand(time(NULL));

  for (int i = 0; i < compute.buffer_capacity; ++i) {
	int min = 0;
	int max = 1024;
	a[i] = rand() % (max + 1 - min) + min;
	b[i] = rand() % (max + 1 - min) + min;
  }

  dct_set_buffer(compute, 0, 0);
  dct_set_buffer(compute, 1, 1);

  dct_set_kernel(compute, kernel_source, "add");
  dct_execute_kernel(compute);

  dct_get_buffer(compute, 2, 2);

//  for (int i = 0; i < compute.buffer_capacity; ++i) {
//	printf("%d: %d + %d = %d\n", i, a[i], b[i], r[i]);
//  }

  dct_free_compute(compute);
  dct_free_file(kernel_source);

  return 0;
}
