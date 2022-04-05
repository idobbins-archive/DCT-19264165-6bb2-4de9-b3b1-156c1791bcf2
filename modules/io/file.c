
#include "io.h"

#include "dct.h"

#include <stdio.h>
#include <stdlib.h>

void dct_load_file(const char *path, dct_source_t *source) {
  FILE *file = fopen(path, "rb");

  fseek(file, 0, SEEK_END);
  source->size = ftell(file);
  fseek(file, 0, SEEK_SET);

  source->file = malloc(source->size + 1);
  fread(source->file, source->size, 1, file);

  fclose(file);
}

void dct_free_file(dct_source_t source){
  free(source.file);
}
