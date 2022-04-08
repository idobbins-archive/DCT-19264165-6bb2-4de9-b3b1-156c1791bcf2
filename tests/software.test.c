
#include "dct.h"
#include "io.h"
#include "linalg.h"

#include <png.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const int DCT_DEGREE = 8 * 4;

void compute_dct(dct_matrix_t *result) {
  for (int i = 0; i < DCT_DEGREE; ++i) {
	for (int j = 0; j < DCT_DEGREE; ++j) {
	  float rt_t = sqrtf(2) / sqrtf((float)DCT_DEGREE);
	  float a_i = i == 0 ? 1 / sqrtf(2) : 1;
	  float c_n = (float)i * (2.0f * (float)j + 1) * DCT_PI;
	  float c_d = 2.0f * (float)DCT_DEGREE;

	  float r = rt_t * a_i * cosf(c_n / c_d);

	  result->data[i][j] = r;
	}
  }
}

int main(int argc, char **argv) {

  if (argc != 3) {
	printf("%s\n", "Invalid number of arguments provided. exiting now...");
	exit(1);
  }

  dct_png_t png;
  dct_load_png(argv[1], &png);

  dct_matrix_t dct;
  dct_init_matrix(&dct, DCT_DEGREE, DCT_DEGREE);
  compute_dct(&dct);

  dct_matrix_t c_x;
  dct_init_matrix(&c_x, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t x_ct;
  dct_init_matrix(&x_ct, DCT_DEGREE, DCT_DEGREE);
  dct_matrix_transpose(&x_ct, c_x);

  dct_matrix_t x;
  dct_init_matrix(&x, DCT_DEGREE, DCT_DEGREE);

  srand(time(NULL));

  int chunk_count = (png.width * png.height) / (DCT_DEGREE * DCT_DEGREE);
  for (int k = 0; k < chunk_count; ++k) {
	int c = k % (png.width / DCT_DEGREE);
	int r = k / (png.width / DCT_DEGREE);

	unsigned char rc = (rand() %(255 - 0 + 1)) + 0;
	unsigned char bc = (rand() %(255 - 0 + 1)) + 0;
	unsigned char gc = (rand() %(255 - 0 + 1)) + 0;

	for(int i = 0; i < DCT_DEGREE; i++) {
	  png_bytep row = png.row_pointers[(r * DCT_DEGREE) + i];
	  for(int j = 0; j < DCT_DEGREE; j++) {
		png_bytep px = &(row[(c * DCT_DEGREE + j)* 4]);
		px[0] = rc;
		px[1] = bc;
		px[2] = gc;
		px[3] = 255;
	  }
	}
  }

  dct_write_png(argv[2], &png);

  //  dct_print_matrix(dct);

  dct_free_matrix(dct);
  dct_free_png(png);

  return 0;
}