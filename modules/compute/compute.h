
#ifndef DCT_MODULES_COMPUTE_COMPUTE_H_
#define DCT_MODULES_COMPUTE_COMPUTE_H_

#include <stddef.h>

typedef struct dct_source_t dct_source_t;
typedef struct dct_compute_t dct_compute_t;

void dct_init_compute(dct_compute_t *compute);
void dct_free_compute(dct_compute_t compute);

void dct_set_buffer(dct_compute_t compute, size_t compute_index, size_t driver_index);
void dct_get_buffer(dct_compute_t compute, size_t compute_index, size_t driver_index);

void dct_set_kernel(dct_compute_t compute, dct_source_t source, const char *name);
void dct_execute_kernel(dct_compute_t compute);

#endif//DCT_MODULES_COMPUTE_COMPUTE_H_
