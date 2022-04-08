
#include "../include/dct.h"

#include "actions.h"

void dct_compute_quantize(dct_matrix_t *result, int d, int p){
  for (int i = 0; i < d; ++i) {
	for (int j = 0; j < d; ++j) {
	  result->data[i][j] = 8 * (float)p * ((float)i + (float)j + 1);
	}
  }
}
