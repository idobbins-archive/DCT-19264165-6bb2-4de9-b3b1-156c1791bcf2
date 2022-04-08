
#ifndef DCT_INCLUDE_DCT_H_
#define DCT_INCLUDE_DCT_H_

#include <stddef.h>

extern const float DCT_PI;

typedef struct dct_source_t dct_source_t;
typedef struct dct_compute_t dct_compute_t;
typedef struct dct_matrix_t dct_matrix_t;

struct dct_source_t {
  size_t size;
  void*	file;
};

struct dct_png_t {
  size_t width, height;
  unsigned char color_type;
  unsigned char bit_depth;
  void **row_pointers;
};

struct dct_compute_t {
  dct_source_t kernel_source;
  void*	driver;

  size_t buffer_count;
  size_t buffer_capacity;
  size_t buffer_item_size;
  size_t buffer_size;
  void** buffers;
};

struct dct_matrix_t {
  size_t width;
  size_t height;
  float **data;
};

#endif//DCT_INCLUDE_DCT_H_
