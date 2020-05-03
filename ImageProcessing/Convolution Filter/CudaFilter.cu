#include "CudaFilter.cuh"

#include "Image.h"
#include "Kernel.h"

void *CudaFilter::copyToGRAM(int size, void *data)
{
	void * c_data;
	cudaError_t error;

	// Alocate GPU memory
	error = cudaMalloc(&c_data, size);
	if (error != cudaSuccess)
	{
		cudaFree(c_data);
		return nullptr;
	}

	// Copy Data to GPU memory
	error = cudaMemcpy(c_data, data, size, cudaMemcpyHostToDevice);
	if (error != cudaSuccess)
	{
		cudaFree(c_data);
		return nullptr;
	}
	return c_data;

}

__global__ void c_applyFilter(float *kernelData, int kernelWidth, int kernelHeight, void *imgData, int imageWidth, int imageHeight, void * res)
{
	Pixel_t * imageData = (Pixel_t *)imgData;
	Pixel_t * result = (Pixel_t *)res;

	int block = blockIdx.x;
	int thread = threadIdx.x;
	int x1, y1;
	float red, green, blue;

	for (int j = block; j < imageHeight; j += 128)
	{
		for (int b = thread; b < imageWidth; b += 128)
		{
			red = 0;
			green = 0;
			blue = 0;

			for (int x = 0; x < kernelHeight; x++)
			{
				for (int y = 0; y < kernelWidth; y++)
				{
					x1 = b - kernelWidth / 2 + x;
					y1 = j - kernelHeight / 2 + y;

					if ((x1 < 0) || (x1 >= imageWidth))
					{
						x1 = (imageWidth - x1) % imageWidth;
					}

					if ((y1 < 0) || (y1 >= imageHeight))
					{
						y1 = (imageHeight - y1) % imageHeight;
					}

					red += imageData[y1*imageWidth + x1].red * kernelData[x*kernelWidth + y];
					green += imageData[y1*imageWidth + x1].green * kernelData[x*kernelWidth + y];
					blue += imageData[y1*imageWidth + x1].blue * kernelData[x*kernelWidth + y];
				}
			}

			red = red > 0 ? (red > 255 ? 255 : red) : 0;
			green = green > 0 ? (green > 255 ? 255 : green) : 0;
			blue = blue > 0 ? (blue > 255 ? 255 : blue) : 0;

			result[j*imageWidth + b].red = (unsigned char)red;
			result[j*imageWidth + b].green = (unsigned char)green;
			result[j*imageWidth + b].blue = (unsigned char)blue;
		}
	}
}


Image * CudaFilter::applyFilter()
{
	int imageSize = image->getHeight()*image->getWidth() * sizeof(Pixel_t);
	int kernelSize = kernel->getHeight()*kernel->getWidth() * sizeof(float);

	// Copy data to GPU memory
	void * c_kernel = copyToGRAM(kernelSize, kernel->getData());
	void * c_image = copyToGRAM(imageSize, image->getData());
	void * c_result;

	cudaMalloc(&c_result, imageSize);
	cudaDeviceSynchronize();

	if (c_kernel == nullptr || c_image == nullptr)
		return nullptr;

	c_applyFilter << < 128, 128 >> > ((float *)c_kernel, kernel->getWidth(), kernel->getHeight(), (Pixel_t *)c_image, image->getWidth(), image->getHeight(), (Pixel_t *)c_result);
	cudaDeviceSynchronize();

	Pixel_t *result = new Pixel_t[image->getWidth()*image->getHeight()];
	cudaMemcpy(result, c_result, imageSize, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	cudaFree(c_kernel);
	cudaFree(c_image);
	cudaFree(c_result);

	return new Image(image->getWidth(), image->getHeight(), result);
}
