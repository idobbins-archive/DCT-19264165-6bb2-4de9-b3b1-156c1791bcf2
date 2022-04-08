
#include "../include/dct.h"

#include "actions.h"

#include <math.h>

void dct_compute_transform(dct_matrix_t *result, int d) {
  for (int i = 0; i < d; ++i) {
	for (int j = 0; j < d; ++j) {
	  float rt_t = sqrtf(2) / sqrtf((float)d);
	  float a_i = i == 0 ? 1 / sqrtf(2) : 1;
	  float c_n = (float)i * (2.0f * (float)j + 1) * DCT_PI;
	  float c_d = 2.0f * (float)d;

	  float r = rt_t * a_i * cosf(c_n / c_d);

	  result->data[i][j] = r;
	}
  }
}