
#include "dct.h"
#include "io.h"
#include "linalg.h"

#include <png.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const int DCT_DEGREE = 8;

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

  dct_matrix_t dct_t;
  dct_init_matrix(&dct_t, DCT_DEGREE, DCT_DEGREE);
  dct_matrix_transpose(&dct_t, dct);

  dct_matrix_t rx;
  dct_init_matrix(&rx, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t rx_r1;
  dct_init_matrix(&rx_r1, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t rx_r2;
  dct_init_matrix(&rx_r2, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t gx;
  dct_init_matrix(&gx, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t gx_r1;
  dct_init_matrix(&gx_r1, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t gx_r2;
  dct_init_matrix(&gx_r2, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t bx;
  dct_init_matrix(&bx, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t bx_r1;
  dct_init_matrix(&bx_r1, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t bx_r2;
  dct_init_matrix(&bx_r2, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t ax;
  dct_init_matrix(&ax, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t ax_r1;
  dct_init_matrix(&ax_r1, DCT_DEGREE, DCT_DEGREE);

  dct_matrix_t ax_r2;
  dct_init_matrix(&ax_r2, DCT_DEGREE, DCT_DEGREE);

  int chunk_count = (png.width * png.height) / (DCT_DEGREE * DCT_DEGREE);
  for (int k = 0; k < chunk_count; ++k) {
	int c = k % (png.width / DCT_DEGREE);
	int r = k / (png.width / DCT_DEGREE);

	for(int i = 0; i < DCT_DEGREE; i++) {
	  png_bytep row = png.row_pointers[(r * DCT_DEGREE) + i];
	  for(int j = 0; j < DCT_DEGREE; j++) {
		png_bytep px = &(row[(c * DCT_DEGREE + j)* 4]);
		rx.data[i][j] = (float)px[0] - 128.0f;
		gx.data[i][j] = (float)px[1] - 128.0f;
		bx.data[i][j] = (float)px[2] - 128.0f;
		ax.data[i][j] = (float)px[3] - 128.0f;
	  }
	}

	dct_matrix_mul(&rx_r1, dct, rx);
	dct_matrix_mul(&rx_r2, rx_r1, dct_t);

	for (int i = 0; i < DCT_DEGREE; ++i) {
	  for (int j = 0; j < DCT_DEGREE; ++j) {
		rx_r2.data[i][j] = (float)roundf(rx_r2.data[i][j]);
		if (i + j >= DCT_DEGREE - 1) rx_r2.data[i][j] = 0;
	  }
	}

	dct_matrix_mul(&rx_r1, dct_t, rx_r2);
	dct_matrix_mul(&rx, rx_r1, dct);

	dct_matrix_mul(&gx_r1, dct, gx);
	dct_matrix_mul(&gx_r2, gx_r1, dct_t);

	for (int i = 0; i < DCT_DEGREE; ++i) {
	  for (int j = 0; j < DCT_DEGREE; ++j) {
		if (i + j >= DCT_DEGREE - 1) gx_r2.data[i][j] = 0;
	  }
	}

	dct_matrix_mul(&gx_r1, dct_t, gx_r2);
	dct_matrix_mul(&gx, gx_r1, dct);

	dct_matrix_mul(&bx_r1, dct, bx);
	dct_matrix_mul(&bx_r2, bx_r1, dct_t);

	for (int i = 0; i < DCT_DEGREE; ++i) {
	  for (int j = 0; j < DCT_DEGREE; ++j) {
		if (i + j >= DCT_DEGREE - 1) bx_r2.data[i][j] = 0;
	  }
	}

	dct_matrix_mul(&bx_r1, dct_t, bx_r2);
	dct_matrix_mul(&bx, bx_r1, dct);

	dct_matrix_mul(&ax_r1, dct, ax);
	dct_matrix_mul(&ax_r2, ax_r1, dct_t);

	for (int i = 0; i < DCT_DEGREE; ++i) {
	  for (int j = 0; j < DCT_DEGREE; ++j) {
		if (i + j >= DCT_DEGREE - 1) ax_r2.data[i][j] = 0;
	  }
	}

	dct_matrix_mul(&ax_r1, dct_t, ax_r2);
	dct_matrix_mul(&ax, ax_r1, dct);

	for(int i = 0; i < DCT_DEGREE; i++) {
	  png_bytep row = png.row_pointers[(r * DCT_DEGREE) + i];
	  for(int j = 0; j < DCT_DEGREE; j++) {
		png_bytep px = &(row[(c * DCT_DEGREE + j)* 4]);
		px[0] = (png_byte)(rx.data[i][j] + 128.0f);
		px[1] = (png_byte)(gx.data[i][j] + 128.0f);
		px[2] = (png_byte)(bx.data[i][j] + 128.0f);
		px[3] = (png_byte)(ax.data[i][j] + 128.0f);
	  }
	}
  }

  dct_write_png(argv[2], &png);

  dct_free_matrix(rx);
  dct_free_matrix(rx_r1);
  dct_free_matrix(rx_r2);


  dct_free_matrix(gx);
  dct_free_matrix(gx_r1);
  dct_free_matrix(gx_r2);

  dct_free_matrix(bx);
  dct_free_matrix(bx_r1);
  dct_free_matrix(bx_r2);

  dct_free_matrix(ax);
  dct_free_matrix(ax_r1);
  dct_free_matrix(ax_r2);

  dct_free_matrix(dct);
  dct_free_png(png);

  return 0;
}