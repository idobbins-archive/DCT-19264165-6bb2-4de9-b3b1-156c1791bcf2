
#ifndef DCT_MODULES_ACTIONS_ACTIONS_H_
#define DCT_MODULES_ACTIONS_ACTIONS_H_

typedef struct dct_matrix_t dct_matrix_t;

void dct_compress(const char* path, int d, float p);
void dct_expand(const char* path);

void dct_compute_transform(dct_matrix_t *result, int d);
void dct_compute_quantize(dct_matrix_t *result, int d, float p);

#endif//DCT_MODULES_ACTIONS_ACTIONS_H_
