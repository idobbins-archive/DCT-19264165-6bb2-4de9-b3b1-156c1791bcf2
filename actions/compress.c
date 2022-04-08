
/*

Image compression function

Contains the core method called from the runtime. Also has helper functions
to reduce the complexity of the implementation.

Does not currently export any compressed image. It performs the DCT and Quantization
and immediately reverses the procedure, outputting a reconstructed image.

*/

#include "actions.h"

#include "dct.h"
#include "io.h"
#include "linalg.h"

#include "png.h"

#include <stdio.h>
#include <math.h>

typedef struct split_rgba_t split_rgba_t;

struct split_rgba_t {
  dct_matrix_t rgba[4];
  int d;
};

static void init_split_rgba(split_rgba_t *s, int d) {
  for (int i = 0; i < 4; ++i) {
	dct_init_matrix(&s->rgba[i], d, d);
  }
  s->d = d;
}

static void free_split_rgba(split_rgba_t s){
  for (int i = 0; i < 4; ++i) {
	dct_free_matrix(s.rgba[i]);
  }
}

static void split_chunk_rgba(split_rgba_t s, int x, int y, dct_png_t png) {
  for (int i = 0; i < s.d; i++) {
	png_bytep row = png.row_pointers[(y * s.d) + i];

	for (int j = 0; j < s.d; j++) {
	  png_bytep px = &(row[(x * s.d + j) * 4]);

	  for (int k = 0; k < 4; ++k) {
		s.rgba[k].data[i][j] = (float)px[k] - 128.0f;
	  }
	}
  }
}

static void merge_chunk_rgba(split_rgba_t s, int x, int y, dct_png_t png){
  for (int i = 0; i < s.d; i++) {
	png_bytep row = png.row_pointers[(y * s.d) + i];

	for (int j = 0; j < s.d; j++) {
	  png_bytep px = &(row[(x * s.d + j) * 4]);

	  for (int k = 0; k < 4; ++k) {
		px[k] = (png_byte)(s.rgba[k].data[i][j] + 128.0f);
	  }
	}
  }
}

static void apply_dct_rgba(split_rgba_t s, dct_matrix_t dct, dct_matrix_t dct_t){
  for (int i = 0; i < 4; ++i) {
	dct_matrix_t a = s.rgba[i];
	dct_matrix_mul(&a, dct, a);
	dct_matrix_mul(&a, a, dct_t);
  }
}

static void reverse_dct_rgba(split_rgba_t s, dct_matrix_t dct, dct_matrix_t dct_t){
  for (int i = 0; i < 4; ++i) {
	dct_matrix_t a = s.rgba[i];
	dct_matrix_mul(&a, dct_t, a);
	dct_matrix_mul(&a, a, dct);
  }
}

static void apply_q_rgba(split_rgba_t s, int d, dct_matrix_t q){
  for (int i = 0; i < d; ++i) {
	for (int j = 0; j < d; ++j) {
	  for (int k = 0; i < 4; ++i) {
		dct_matrix_t a = s.rgba[k];

		float v = a.data[i][j] / q.data[i][j];
		a.data[i][j] = (float)roundf(v);
	  }
	}
  }
}

static void reverse_q_rgba(split_rgba_t s, int d, dct_matrix_t q){
  for (int i = 0; i < d; ++i) {
	for (int j = 0; j < d; ++j) {
	  for (int k = 0; i < 4; ++i) {
		dct_matrix_t a = s.rgba[k];
		a.data[i][j] = a.data[i][j] * q.data[i][j];
	  }
	}
  }
}

void dct_compress(const char *path, int d, float p) {

  // hide cursor
  printf("\e[?25l");

  printf("Discrete Cosine Transform (DCT) Image Compression\n\n");
  printf("Settings:\n");
  printf("\tImage: %s\n", path);
  printf("\tDepth: %d\n", d);
  printf("\tP-value: %.2f\n\n", p);

  dct_png_t png;
  dct_load_png(path, &png);

  dct_matrix_t dct;
  dct_init_matrix(&dct, d, d);
  dct_compute_transform(&dct, d);

  dct_matrix_t dct_t;
  dct_init_matrix(&dct_t, d, d);
  dct_matrix_transpose(&dct_t, dct);

  dct_matrix_t q;
  dct_init_matrix(&q, d, d);
  dct_compute_quantize(&q, d, p);

  split_rgba_t split;
  init_split_rgba(&split, d);

  const int chunk_count = (png.width * png.height) / (d * d);

  /*

  'chunks' are iterated in serial fashion, this
   is where it would be good to focus on concurrent
   implementations in the future.

  */
  for (int k = 0; k < chunk_count; ++k) {
	int x = k % (png.width / d);
	int y = k / (png.width / d);

	// need to operate on rgba channels individually.
	split_chunk_rgba(split, x, y, png);

	// immediate reversal of computation is sufficient for now.
	apply_dct_rgba(split, dct, dct_t);
	apply_q_rgba(split, d, q);
	reverse_q_rgba(split, d, q);
	reverse_dct_rgba(split, dct, dct_t);

	// can't have an image without its parts (rgba).
	merge_chunk_rgba(split, x, y, png);

	// update progress
	float progress = ((float)k / ((float)chunk_count - 1)) * 100.0f;
	printf("\rCompressing image: %2.0f%% <%d/%d>", progress, k, chunk_count);
	fflush(stdout);
  }

  printf(", done.\n");

  const char* out_path = "./out.png";
  printf("Writing image to %s...", out_path);
  fflush(stdout);

  dct_write_png("./out.png", &png);
  printf(" done.\n");

  free_split_rgba(split);
  dct_free_matrix(q);
  dct_free_matrix(dct);
  dct_free_matrix(dct_t);
  dct_free_png(png);

  // show cursor
  printf("\e[?25h");
}