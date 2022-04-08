
#include "linalg.h"

#include "dct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const float DCT_PI = 3.14159265359f;

void dct_print_matrix(dct_matrix_t a) {
  printf("Matrix: %zu X %zu\n", a.width, a.height);
  for (int i = 0; i < a.height; ++i) {
	for (int j = 0; j < a.width; ++j) {
	  printf("%10.2f ", a.data[i][j]);
	}
	printf("\n");
  }
}

void dct_init_matrix(dct_matrix_t *a, size_t width, size_t height) {

  a->width = width;
  a->height = height;

  a->data = malloc(height * sizeof(float *));

  for (int i = 0; i < height; ++i) {
	a->data[i] = calloc(width, sizeof(float));
  }
}

void dct_free_matrix(dct_matrix_t a) {
  for (int i = 0; i < a.height; ++i) {
	free(a.data[i]);
  }

  free(a.data);
}

void dct_copy_matrix(dct_matrix_t *result, dct_matrix_t a){
  for (int i = 0; i < a.height; ++i) {
	for (int j = 0; j < a.width; ++j) {
	  result->data[i][j] = a.data[i][j];
	}
  }
}

void dct_matrix_transpose(dct_matrix_t *result, dct_matrix_t a) {
  for (int i = 0; i < a.width; ++i) {
	for (int j = 0; j < a.height; ++j) {
	  result->data[i][j] = a.data[j][i];
	}
  }
}

float dct_dot_product(const float *a, const float *b, size_t size) {
  float result = 0;

  for (int i = 0; i < size; ++i) {
	result += a[i] * b[i];
  }

  return result;
}

void dct_matrix_mul(dct_matrix_t *result, dct_matrix_t a, dct_matrix_t b) {
  // check for compatible matrix dimensions
  if (a.width != b.height) exit(1);

  dct_matrix_t ac;
  dct_init_matrix(&ac, a.width, a.height);
  dct_copy_matrix(&ac, a);

  dct_matrix_t bt;
  dct_init_matrix(&bt, b.height, b.width);

  dct_matrix_transpose(&bt, b);

  for (int i = 0; i < b.height; ++i) {
	for (int j = 0; j < b.width; ++j) {
	  float dot = dct_dot_product(ac.data[i], bt.data[j], a.width);
	  result->data[i][j] = dot;
	}
  }

  dct_free_matrix(ac);
  dct_free_matrix(bt);
}

void dct_matrix_scalar(dct_matrix_t *result, dct_matrix_t a, float s) {
  for (int i = 0; i < a.height; ++i) {
	for (int j = 0; j < a.width; ++j) {
	  result->data[i][j] = a.data[i][j] * s;
	}
  }
}
