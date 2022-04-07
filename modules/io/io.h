
#ifndef DCT_MODULES_IO_IO_H_
#define DCT_MODULES_IO_IO_H_

typedef struct dct_source_t dct_source_t;

void dct_load_file(const char *path, dct_source_t *source);
void dct_free_file(dct_source_t source);

typedef struct dct_png_t dct_png_t;

void dct_load_png(const char *path, dct_png_t *image);
void dct_free_png(dct_png_t image);

#endif//DCT_MODULES_IO_IO_H_
