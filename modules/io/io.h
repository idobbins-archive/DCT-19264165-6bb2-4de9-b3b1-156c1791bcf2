
#ifndef DCT_MODULES_IO_IO_H_
#define DCT_MODULES_IO_IO_H_

typedef struct dct_source_t dct_source_t;

void dct_load_file(const char *path, dct_source_t *source);
void dct_free_file(dct_source_t source);

#endif//DCT_MODULES_IO_IO_H_
