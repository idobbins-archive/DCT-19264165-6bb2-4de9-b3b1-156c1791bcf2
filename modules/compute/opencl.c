
#include "compute.h"

#include "dct.h"

#include <OpenCL/opencl.h>

typedef struct dct_driver_t dct_driver_t;

struct dct_driver_t {
  cl_int status;

  cl_platform_id platform_id;
  cl_uint platform_count;

  cl_device_id device_id;
  cl_uint device_count;

  cl_context context;
  cl_command_queue command_queue;

  cl_program program;
  cl_kernel kernel;

  cl_mem *buffers;
};

static void init_driver(dct_driver_t **driver, size_t size) {
  *driver = malloc(sizeof(dct_driver_t));

  dct_driver_t *ref = *driver;

  ref->status = clGetPlatformIDs(1, &ref->platform_id, &ref->platform_count);
  ref->status = clGetDeviceIDs(ref->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &ref->device_id, &ref->device_count);

  ref->context = clCreateContext(NULL, 1, &ref->device_id, NULL, NULL, &ref->status);
  ref->command_queue = clCreateCommandQueue(ref->context, ref->device_id, 0, &ref->status);

  ref->buffers = malloc(3 * sizeof(cl_mem *));
  for (int i = 0; i < 3; ++i) {
	ref->buffers[i] = clCreateBuffer(ref->context, CL_MEM_READ_ONLY, size, NULL, &ref->status);
  }
}

static void free_driver(dct_driver_t *driver) {
  clFlush(driver->command_queue);
  clFinish(driver->command_queue);
  clReleaseKernel(driver->kernel);
  clReleaseProgram(driver->program);

  for (int i = 0; i < 3; ++i) {
	clReleaseMemObject(driver->buffers[i]);
  }

  clReleaseCommandQueue(driver->command_queue);
  clReleaseContext(driver->context);
  free(driver);
}

void dct_init_compute(dct_compute_t *compute) {
  // for the time being, we are manually initializing our buffers.
  compute->buffer_count = 3;
  compute->buffer_capacity = 1024;
  compute->buffer_item_size = sizeof(float);
  compute->buffer_size = compute->buffer_capacity * compute->buffer_item_size;
  compute->buffers = malloc(compute->buffer_count * compute->buffer_capacity * sizeof(int *));

  for (int i = 0; i < compute->buffer_count; ++i) {
	compute->buffers[i] = malloc(compute->buffer_capacity * compute->buffer_item_size);
  }

  dct_driver_t *driver;
  init_driver(&driver, compute->buffer_size);

  compute->driver = driver;
}

void dct_free_compute(dct_compute_t compute) {
  free_driver((dct_driver_t *)compute.driver);

  for (int i = 0; i < compute.buffer_count; ++i) {
	free(compute.buffers[i]);
  }

  free(compute.buffers);
}

void dct_set_buffer(dct_compute_t compute, void *buffer, size_t index) {
  dct_driver_t *driver = compute.driver;
  driver->status = clEnqueueWriteBuffer(driver->command_queue, driver->buffers[index], CL_TRUE, 0, compute.buffer_size, buffer, 0, NULL, NULL);
}

void dct_get_buffer(dct_compute_t compute, void *buffer, size_t index) {
  dct_driver_t *driver = compute.driver;
  clEnqueueReadBuffer(driver->command_queue, driver->buffers[index], CL_TRUE, 0, compute.buffer_size, buffer, 0, NULL, NULL);
}

void dct_set_kernel(dct_compute_t compute, dct_source_t source, const char *name) {
  dct_driver_t *driver = compute.driver;
  driver->program = clCreateProgramWithSource(driver->context, 1, (const char **)&source, (const size_t *)&source.size, &driver->status);

  driver->status = clBuildProgram(driver->program, 1, &driver->device_id, NULL, NULL, NULL);

  driver->kernel = clCreateKernel(driver->program, name, &driver->status);

  for (int i = 0; i < 3; ++i) {
	driver->status = clSetKernelArg(driver->kernel, i, sizeof(cl_mem), (void *)&driver->buffers[i]);
  }
}

void dct_execute_kernel(dct_compute_t compute) {
  dct_driver_t *driver = compute.driver;

  size_t group_size = 64;
  driver->status = clEnqueueNDRangeKernel(driver->command_queue, driver->kernel, 1, NULL, &compute.buffer_size, &group_size, 0, NULL, NULL);
}
