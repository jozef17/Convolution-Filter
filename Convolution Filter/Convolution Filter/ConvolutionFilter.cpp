#include "ConvolutionFilter.h"

#include <windows.h>
#include <iomanip>
#include <iostream>

#include "Image.h"
#include "Kernel.h"

Kernel *ConvolutionFilter::specifyKernel()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	int width, height;
	float** data;

	do
	{
		std::cout << "Specify Kernel height: ";
		std::cin >> height;
		if (height % 2 == 0)
		{
			SetConsoleTextAttribute(h, 12);
			std::cout << "Error: Kernel height must be odd number" << std::endl;
			SetConsoleTextAttribute(h, 15);
		}
	} while (height % 2 == 0);

	do
	{
		std::cout << "Specify Kernel width: ";
		std::cin >> width;
		if (width % 2 == 0)
		{
			SetConsoleTextAttribute(h, 12);
			std::cout << "Error: Kernel width must be odd number" << std::endl;
			SetConsoleTextAttribute(h, 15);
		}
	} while (width % 2 == 0);

	std::cout << "Specify Kernel (" << height << "x" << width << ") : ";
	data = new float*[height];

	for (int j = 0; j < height; j++)
	{
		data[j] = new float[width];

		for (int b = 0; b < width; b++)
		{
			std::cin >> data[j][b];
		}
	}

	return new Kernel(width, height, data);
}

ConvolutionFilter::ConvolutionFilter()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);
}

void ConvolutionFilter::setImage()
{
	std::string filename;
	int width, height;

	std::cout << "Insert filename: ";
	std::cin >> filename;
	std::cout << "Specify image height: ";
	std::cin >> height;
	std::cout << "Specfy image width:";
	std::cin >> width;

	image = new Image(width, height, filename);
}

void ConvolutionFilter::setKernel()
{
	int option;
	std::cout << "Select Kernel:" << std::endl;
	std::cout << "\t 0 - own (specify)" << std::endl;
	std::cout << "\t 1 - Inedntity 9x9" << std::endl;
	std::cout << "\t 2 - Gausian blur 9x9" << std::endl;
	std::cout << "\t 3 - Sharpen 9x9" << std::endl;
	std::cout << "\t 4 - Edge Detection 9x9" << std::endl;

	std::cin >> option;

	float** kernel = nullptr;
	unsigned char width = 0;
	unsigned char height = 0;

	switch (option) {
	case 1:
		width = 9;
		height = 9;
		kernel = new float*[9];

		kernel[0] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[1] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[2] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[3] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[4] = new float[9]{ 0, 0, 0, 0, 1, 0, 0, 0, 0 };
		kernel[5] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[6] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[7] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[8] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		break;

	case 2:
		width = 9;
		height = 9;
		kernel = new float*[9];

		kernel[0] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[1] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[2] = new float[9]{ 0, 0, 1 / (float)256, 4 / (float)256, 6 / (float)256, 4 / (float)256, 1 / (float)256, 0, 0 };
		kernel[3] = new float[9]{ 0, 0, 4 / (float)256, 16 / (float)256, 24 / (float)256, 16 / (float)256, 4 / (float)256, 0, 0 };
		kernel[4] = new float[9]{ 0, 0, 6 / (float)256, 24 / (float)256, 36 / (float)256, 24 / (float)256, 6 / (float)256, 0, 0 };
		kernel[5] = new float[9]{ 0, 0, 4 / (float)256, 16 / (float)256, 24 / (float)256, 16 / (float)256, 4 / (float)256, 0, 0 };
		kernel[6] = new float[9]{ 0, 0, 1 / (float)256, 4 / (float)256, 6 / (float)256, 4 / (float)256, 1 / (float)256, 0, 0 };
		kernel[7] = new float[9]{ 0, 0,	0, 0, 0, 0, 0, 0, 0 };
		kernel[8] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		break;

	case 3:
		width = 9;
		height = 9;
		kernel = new float*[9];

		kernel[0] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[1] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		kernel[2] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		kernel[3] = new float[9]{ 0, 0, 0,  0, -1,  0, 0, 0, 0 };
		kernel[4] = new float[9]{ 0, 0, 0, -1,  5, -1, 0, 0, 0 };
		kernel[5] = new float[9]{ 0, 0, 0,  0, -1,  0, 0, 0, 0 };
		kernel[6] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		kernel[7] = new float[9]{ 0, 0,	0,  0,  0,  0, 0, 0, 0 };
		kernel[8] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		break;

	case 4:
		width = 9;
		height = 9;
		kernel = new float*[9];

		kernel[0] = new float[9]{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		kernel[1] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		kernel[2] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		kernel[3] = new float[9]{ 0, 0, 0, -1, -1, -1, 0, 0, 0 };
		kernel[4] = new float[9]{ 0, 0, 0, -1,  5, -1, 0, 0, 0 };
		kernel[5] = new float[9]{ 0, 0, 0, -1, -1, -1, 0, 0, 0 };
		kernel[6] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		kernel[7] = new float[9]{ 0, 0,	0,  0,  0,  0, 0, 0, 0 };
		kernel[8] = new float[9]{ 0, 0, 0,  0,  0,  0, 0, 0, 0 };
		break;

	default:
		this->kernel = specifyKernel();
		return;
	}

	this->kernel = new Kernel(width, height, kernel);
	this->kernel->print();
}

ConvolutionFilter::~ConvolutionFilter()
{
	if (kernel != nullptr)
		delete kernel;
	if (image != nullptr)
		delete image;
}
