#include <stdio.h>
#include <CL/cl.h>

size_t gws[1] = {51200};
size_t lws[1] = {1};

cl_platform_id platform[2];		// OpenCL Platform
cl_device_id device;			// compute device
cl_context context;			    // compute context
cl_command_queue queue;			// compute command queue

cl_int nProgram = 1;
cl_program program[1];			// compute program
cl_kernel kernel[1];			// compute kernel

const char *source[1][1] = {{"#include <atomicTest.cl>"}};
const char *kernelName[1] = {"atomicTest"};

int main(int argc, char const *argv[]) {
  int i;
  #include <opencl_start.h>
  #include <opencl_build.h>

  setvbuf (stdout, NULL, _IONBF, 0);

  int lock = 0;
  cl_mem d_lock = clCreateBuffer (context,
        CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        sizeof (cl_int), &lock, NULL);

  cl_int *rop = (cl_int *) malloc (gws[0] * sizeof (cl_int));
  cl_mem d_rop = clCreateBuffer (context, CL_MEM_READ_WRITE,
        gws[0] * sizeof (cl_int), NULL, NULL);

  int counter = 0;
  cl_mem d_counter = clCreateBuffer (context,
        CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        sizeof (cl_int), &counter, NULL);

  clSetKernelArg(kernel[0], 0, sizeof (cl_mem), (void *) &d_lock);
  clSetKernelArg(kernel[0], 1, sizeof (cl_mem), (void *) &d_rop);
  clSetKernelArg(kernel[0], 2, sizeof (cl_mem), (void *) &d_counter);
  clEnqueueNDRangeKernel (
    	 queue, kernel[0], 1, NULL,
       gws, lws, 0, NULL, NULL);

  clFinish (queue);

  clEnqueueReadBuffer (queue, d_rop, CL_TRUE, 0,
          gws[0]*sizeof (cl_int), rop, 0, NULL, NULL);

  int sum=0;
  for (i=0; i<gws[0]; ++i) sum += rop[i];

  printf ("Final sum = %i\n", sum);

  return 0;
}
