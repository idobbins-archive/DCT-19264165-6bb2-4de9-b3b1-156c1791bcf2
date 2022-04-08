
#ifndef DCT_MODULES_LINALG_LINALG_H_
#define DCT_MODULES_LINALG_LINALG_H_


#include <stddef.h>


typedef struct dct_matrix_t dct_matrix_t;

void dct_print_matrix(dct_matrix_t a);

void dct_init_matrix(dct_matrix_t *a, size_t width, size_t height);
void dct_free_matrix(dct_matrix_t a);

void dct_matrix_transpose(dct_matrix_t *result, dct_matrix_t a);

float dct_dot_product(const float *a, const float *b, size_t size);

void dct_matrix_mul(dct_matrix_t *result, dct_matrix_t a, dct_matrix_t b);

void dct_matrix_scalar(dct_matrix_t *result, dct_matrix_t a, float s);

#endif//DCT_MODULES_LINALG_LINALG_H_
