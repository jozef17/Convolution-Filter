#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "ConvolutionFilter.h"

__global__ void c_applyFilter(float *kernelData, int kernelWidth, int kernelHeight, void *imageData, int imageWidth, int imageHeight, void * result);

class CudaFilter :
	public ConvolutionFilter
{
private:
	void *copyToGRAM(int size, void *data);

public:
	Image* applyFilter();

};
