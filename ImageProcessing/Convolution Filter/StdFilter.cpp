#include "StdFilter.h"
#include "Image.h"
#include "Kernel.h"

#include <thread>
#include <vector>

#define NUM_THREADS 8

Image * StdFilter::applyFilter()
{
	if (kernel == nullptr)
		return nullptr;
	if (image == nullptr)
		return nullptr;

	Pixel_t *resultImage = new Pixel_t[image->getWidth()*image->getHeight()];

	std::vector<std::thread> threads;

	for (int i = 0; i < NUM_THREADS; i++) {
		threads.push_back(std::thread(
			[&](int id) -> void
		{
			for (unsigned int j = id; j < image->getHeight(); j += NUM_THREADS)
			{
				for (unsigned int b = 0; b < image->getWidth(); b++)
				{
					unsigned int x1, y1;
					float red = 0;
					float green = 0;
					float blue = 0;

					for (unsigned int y = 0; y < kernel->getHeight(); y++)
					{
						for (unsigned int x = 0; x < kernel->getWidth(); x++)
						{
							x1 = b - kernel->getWidth() / 2 + x;
							y1 = j - kernel->getHeight() / 2 + y;

							if ((x1 < 0) || (x1 >= image->getWidth()))
							{
								x1 = (image->getWidth() - x1) % image->getWidth();
							}

							if ((y1 < 0) || (y1 >= image->getHeight()))
							{
								y1 = (image->getHeight() - y1) % image->getHeight();
							}

							Pixel_t pixel = image->get(y1, x1);
							red += pixel.red * kernel->getData()[x][y];
							green += pixel.green * kernel->getData()[x][y];
							blue += pixel.blue * kernel->getData()[x][y];
						} // x
					} // y

					red = red < 0 ? 0 : red > 255 ? 255 : red;
					green = green < 0 ? 0 : green > 255 ? 255 : green;
					blue = blue < 0 ? 0 : blue > 255 ? 255 : blue;

					resultImage[j * image->getWidth() + b].red = (unsigned char)red;
					resultImage[j * image->getWidth() + b].green = (unsigned char)green;
					resultImage[j * image->getWidth() + b].blue = (unsigned char)blue;
				} // b
			} // j
		}
		, i));
	}

	for (int i = 0; i < NUM_THREADS; i++)
		threads[i].join();

	return new Image(image->getWidth(), image->getHeight(), resultImage);
}
