
#include "dct.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct dct_matrix_t dct_matrix_t;

struct dct_matrix_t {
  size_t width;
  size_t height;
  float **data;
};

static void dct_print_matrix(dct_matrix_t m) {
  printf("Matrix: %zu X %zu\n", m.width, m.height);
  for (int i = 0; i < 3; ++i) {
	for (int j = 0; j < 3; ++j) {
	  printf("%.2f  ", m.data[i][j]);
	}
	printf("\n");
  }
  printf("\n");
}

static void dct_init_matrix(dct_matrix_t *matrix, size_t width, size_t height) {

  matrix->width = width;
  matrix->height = height;

  matrix->data = malloc(height * sizeof(float *));

  for (int i = 0; i < height; ++i) {
	matrix->data[i] = calloc(width, sizeof(float));
  }
}

static void dct_free_matrix(dct_matrix_t matrix) {
  for (int i = 0; i < matrix.height; ++i) {
	free(matrix.data[i]);
  }

  free(matrix.data);
}

static void dct_matrix_transpose(dct_matrix_t *result, dct_matrix_t a) {
  for (int i = 0; i < a.width; ++i) {
	for (int j = 0; j < a.height; ++j) {
	  result->data[i][j] = a.data[j][i];
	}
  }
}

static float dct_dot_product(const float *a, const float *b, size_t size) {
  float result = 0;

  for (int i = 0; i < size; ++i) {
	result += a[i] * b[i];
  }

  return result;
}

static void dct_matrix_mul(dct_matrix_t *result, dct_matrix_t a, dct_matrix_t b) {
  // check for compatible matrix dimensions
  if (a.width != b.height) exit(1);

  dct_matrix_t bt;
  dct_init_matrix(&bt, b.height, b.width);

  dct_matrix_transpose(&bt, b);

  for (int i = 0; i < b.height; ++i) {
	for (int j = 0; j < b.width; ++j) {
	  float dot = dct_dot_product(a.data[i], bt.data[j], a.width);
	  result->data[i][j] = dot;
	}
  }

  dct_free_matrix(bt);
}

int main(int argc, char **argv) {

  if (argc != 2) {
	printf("%s\n", "Invalid number of arguments provided. exiting now...");
	exit(1);
  }

  dct_png_t png;
  dct_load_png(argv[1], &png);
  dct_free_png(png);

  dct_matrix_t a;

  dct_init_matrix(&a, 3, 3);

  for (int i = 0, q = 1; i < 3; ++i) {
	for (int j = 0; j < 3; ++j, ++q) {
	  a.data[i][j] = (float)q;
	}
  }

  dct_matrix_t b;

  dct_init_matrix(&b, 3, 3);

  for (int i = 0, q = 1; i < 3; ++i) {
	for (int j = 0; j < 3; ++j, ++q) {
	  b.data[i][j] = (float)q;
	}
  }

  dct_matrix_t result;
  dct_init_matrix(&result, 3, 3);

  dct_matrix_mul(&result, a, b);

  dct_print_matrix(result);

  dct_free_matrix(a);
  dct_free_matrix(b);
  dct_free_matrix(result);

  return 0;
}