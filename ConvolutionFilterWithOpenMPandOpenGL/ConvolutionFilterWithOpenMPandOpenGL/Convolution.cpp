/**
  *
  * @author Jozef Blazicek
  * */

#include "Convolution.h"
#include <omp.h>

convolution_filter::Convolution::~Convolution()
{
	if (kernel != nullptr)
		delete kernel;
	if (image != nullptr)
		delete image;
}

void convolution_filter::Convolution::setImage()
{
	image = convolution_filter::Image::getImage();
}

void convolution_filter::Convolution::setKernel()
{
	kernel = convolution_filter::Kernel::getKernel();
	kernel->print();
}

convolution_filter::Image *convolution_filter::Convolution::applyFilter()
{
	if (kernel == nullptr)
		return nullptr;
	if (image == nullptr)
		return nullptr;

	unsigned int imageWidth = image->getWidth();
	unsigned int imageHeight = image->getHeight();
	unsigned int kernelWidth = kernel->getWidth();
	unsigned int kernelHeight = kernel->getHeight();
	int j = 0;

	Pixel_t *imageData = image->getData();
	Pixel_t *resultImage = new Pixel_t[imageWidth*imageHeight];
	float **kernelData = kernel->getData();

	// For every pixel
#pragma omp parallel for shared(imageHeight, imageWidth, kernelHeight, kernelWidth, imageData, resultImage, kernelData, j)
	for (j = 0; j < imageHeight; j++)
	{
		for (unsigned int b = 0; b < imageWidth; b++)
		{
			// Aply filter0
			unsigned int x1, y1;
			float red = 0;
			float green = 0;
			float blue = 0;

			for (unsigned int y = 0; y < kernelHeight; y++)
			{
				for (unsigned int x = 0; x < kernelWidth; x++)
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

					red += imageData[y1*imageWidth + x1].red * kernelData[x][y];
					green += imageData[y1*imageWidth + x1].green * kernelData[x][y];
					blue += imageData[y1*imageWidth + x1].blue * kernelData[x][y];
				}
			}

			if (red < 0)
				red = 0;
			else if (red > 255)
				red = 255;

			if (green < 0)
				green = 0;
			else if (green > 255)
				green = 255;

			if (blue < 0)
				blue = 0;
			else if (blue > 255)
				blue = 255;

			resultImage[j*imageWidth + b].red = (unsigned char)red;
			resultImage[j*imageWidth + b].green = (unsigned char)green;
			resultImage[j*imageWidth + b].blue = (unsigned char)blue;
		}
	}
	return new Image(imageWidth, imageHeight, resultImage);
}
