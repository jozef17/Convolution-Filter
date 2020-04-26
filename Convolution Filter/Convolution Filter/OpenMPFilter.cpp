#include "OpenMPFilter.h"
#include "Image.h"
#include "Kernel.h"

#include <omp.h>

Image* OpenMPFilter::applyFilter()
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

	//	Pixel_t *imageData = image->getData();
	Pixel_t *resultImage = new Pixel_t[imageWidth*imageHeight];
	float **kernelData = kernel->getData();

	// For every pixel
#pragma omp parallel for shared(imageHeight, imageWidth, kernelHeight, kernelWidth, image, resultImage, kernelData, j)
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

					Pixel_t pixel = image->get(y1, x1);
					red += pixel.red * kernelData[x][y];
					green += pixel.green * kernelData[x][y];
					blue += pixel.blue * kernelData[x][y];
				}
			}

			red = red < 0 ? 0 : red > 255 ? 255 : red;
			green = green < 0 ? 0 : green > 255 ? 255 : green;
			blue = blue < 0 ? 0 : blue > 255 ? 255 : blue;

			resultImage[j*imageWidth + b].red = (unsigned char)red;
			resultImage[j*imageWidth + b].green = (unsigned char)green;
			resultImage[j*imageWidth + b].blue = (unsigned char)blue;
		}
	}

	return new Image(imageWidth, imageHeight, resultImage);
}
