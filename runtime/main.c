
#include "../include/dct.h"

#include "compute.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  if (argc != 2) {
	printf("%s\n", "Invalid number of arguments provided. exiting now...");
	exit(1);
  }

  dct_source_t kernel_source;
  dct_load_file(argv[1], &kernel_source);

  dct_compute_t compute;
  dct_init_compute(&compute);

//  char *source = NULL;
//  size_t size = 0;
//  dct_load_source(argv[1], &source, &size);
//
//  int *a = malloc(BUFFER_SIZE * sizeof(int));
//  int *b = malloc(BUFFER_SIZE * sizeof(int));
//
//  srand(time(NULL));// Initialization, should only be called once.
//  for (int i = 0; i < BUFFER_SIZE; ++i) {
//	int min = 0;
//	int max = 1024;
//	a[i] = rand() % (max + 1 - min) + min;
//	b[i] = rand() % (max + 1 - min) + min;
//  }
//
//  cl_int status;
//
//  cl_platform_id platform_id = NULL;
//  cl_uint platform_count;
//  status = clGetPlatformIDs(1, &platform_id, &platform_count);
//
//  cl_device_id device_id = NULL;
//  cl_uint device_count;
//  status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &device_count);
//
//  cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &status);
//
//  cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &status);
//
//  cl_mem buffer_a = clCreateBuffer(context, CL_MEM_READ_ONLY, BUFFER_SIZE * sizeof(int), NULL, &status);
//  cl_mem buffer_b = clCreateBuffer(context, CL_MEM_READ_ONLY, BUFFER_SIZE * sizeof(int), NULL, &status);
//  cl_mem buffer_r = clCreateBuffer(context, CL_MEM_WRITE_ONLY, BUFFER_SIZE * sizeof(int), NULL, &status);
//
//  status = clEnqueueWriteBuffer(command_queue, buffer_a, CL_TRUE, 0, BUFFER_SIZE * sizeof(int), a, 0, NULL, NULL);
//  status = clEnqueueWriteBuffer(command_queue, buffer_b, CL_TRUE, 0, BUFFER_SIZE * sizeof(int), b, 0, NULL, NULL);
//
//  cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source, (const size_t *)&size, &status);
//
//  status = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
//
//  cl_kernel kernel = clCreateKernel(program, "add", &status);
//
//  status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&buffer_a);
//  status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&buffer_b);
//  status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&buffer_r);
//
//  size_t global_item_size = BUFFER_SIZE;
//  size_t local_item_size = 64;
//  status = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
//
//  int *r = malloc(BUFFER_SIZE * sizeof(int));
//
//  status = clEnqueueReadBuffer(command_queue, buffer_r, CL_TRUE, 0, BUFFER_SIZE * sizeof(int), r, 0, NULL, NULL);
//
////  for (int i = 0; i < BUFFER_SIZE; ++i) {
////	printf("%d + %d = %d\n", a[i], b[i], r[i]);
////  }
//
//  // Clean up
//  status = clFlush(command_queue);
//  status = clFinish(command_queue);
//  status = clReleaseKernel(kernel);
//  status = clReleaseProgram(program);
//  status = clReleaseMemObject(buffer_a);
//  status = clReleaseMemObject(buffer_b);
//  status = clReleaseMemObject(buffer_r);
//  status = clReleaseCommandQueue(command_queue);
//  status = clReleaseContext(context);
//
//  free(a);
//  free(b);
//  free(r);
//
//  free(source);

  dct_free_compute(compute);
  dct_free_file(kernel_source);

  return 0;
}
