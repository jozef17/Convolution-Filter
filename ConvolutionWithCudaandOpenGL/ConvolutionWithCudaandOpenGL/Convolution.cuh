/**
*
* @author Jozef Blazicek
* */

#ifndef BLAZICEK_CONVOLUTION_CUDA
#define BLAZICEK_CONVOLUTION_CUDA

#include "image.h"
#include "kernel.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace convolution_filter;

__global__ void c_applyFilter(float *kernelData, int kernelWidth, int kernelHeight, Pixel_t *imageData, int imageWidth, int imageHeight, Pixel_t * result);

Image *applyFilter(Image *image, Kernel * kernel);
void *copyToGRAM(int size, void *data);

#endif
