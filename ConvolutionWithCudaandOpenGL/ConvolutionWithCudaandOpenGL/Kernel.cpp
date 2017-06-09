/**
  *
  * @author Jozef Blazicek
  * */

#include "Kernel.h"

#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace convolution_filter;

float *asDinamicArray(float *templateData, int width, int height)
{
	float *data = new float[height*width];

	for (int j = 0; j < height*width; j++)
	{
		data[j] = templateData[j];
	}
	return data;
}

Kernel * Kernel::getIdentityKernel()
{
	unsigned char width = 9;
	unsigned char height = 9;
	float templateData[9 * 9] =
	{
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 1, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
	};

	float* data = asDinamicArray(templateData, width, height);
	return new Kernel(width, height, data);
}

Kernel * Kernel::getGausianBlurKernel()
{
	unsigned char width = 9;
	unsigned char height = 9;
	float templateData[9 * 9] =
	{
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 1 / (float)256,  4 / (float)256,  6 / (float)256,  4 / (float)256, 1 / (float)256, 0, 0 ,
		 0, 0, 4 / (float)256, 16 / (float)256, 24 / (float)256, 16 / (float)256, 4 / (float)256, 0, 0 ,
		 0, 0, 6 / (float)256, 24 / (float)256, 36 / (float)256, 24 / (float)256, 6 / (float)256, 0, 0 ,
		 0, 0, 4 / (float)256, 16 / (float)256, 24 / (float)256, 16 / (float)256, 4 / (float)256, 0, 0 ,
		 0, 0, 1 / (float)256,  4 / (float)256,  6 / (float)256,  4 / (float)256, 1 / (float)256, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
		 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
	};

	float* data = asDinamicArray(templateData, width, height);
	return new Kernel(width, height, data);
}

Kernel * Kernel::getSharpenKernel()
{
	unsigned char width = 9;
	unsigned char height = 9;
	float templateData[9 * 9] =
	{
		 0, 0, 0,  0,  0,  0, 0, 0, 0 ,
		 0, 0, 0,  0,  0,  0, 0, 0, 0 ,
		 0, 0, 0,  0,  0,  0, 0, 0, 0 ,
		 0, 0, 0,  0, -1,  0, 0, 0, 0 ,
		 0, 0, 0, -1,  5, -1, 0, 0, 0 ,
		 0, 0, 0,  0, -1,  0, 0, 0, 0 ,
		 0, 0, 0,  0,  0,  0, 0, 0, 0 ,
		 0, 0, 0,  0,  0,  0, 0, 0, 0 ,
		 0, 0, 0,  0,  0,  0, 0, 0, 0 ,
	};

	float* data = asDinamicArray(templateData, width, height);
	return new Kernel(width, height, data);
}

Kernel * Kernel::getEdgeDetectionKernel()
{
	unsigned char width = 9;
	unsigned char height = 9;
	float templateData[9 * 9] =
	{
		 0, 0, 0,  0,  0,  0, 0, 0, 0,
		 0, 0, 0,  0,  0,  0, 0, 0, 0,
		 0, 0, 0,  0,  0,  0, 0, 0, 0,
		 0, 0, 0, -1, -1, -1, 0, 0, 0,
		 0, 0, 0, -1,  9, -1, 0, 0, 0,
		 0, 0, 0, -1, -1, -1, 0, 0, 0,
		 0, 0, 0,  0,  0,  0, 0, 0, 0,
		 0, 0, 0,  0,  0,  0, 0, 0, 0,
		 0, 0, 0,  0,  0,  0, 0, 0, 0,
	};

	float* data = asDinamicArray(templateData, width, height);
	return new Kernel(width, height, data);
}

Kernel * Kernel::specifyKernel()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	int width, height;
	float* data;

	do
	{
		cout << "Specify Kernel height: ";
		cin >> height;
		if (height % 2 == 0)
		{
			SetConsoleTextAttribute(h, 12);
			cout << "Error: Kernel height must be odd number" << endl;
			SetConsoleTextAttribute(h, 15);
		}
	} while (height % 2 == 0);

	do
	{
		cout << "Specify Kernel width: ";
		cin >> width;
		if (width % 2 == 0)
		{
			SetConsoleTextAttribute(h, 12);
			cout << "Error: Kernel width must be odd number" << endl;
			SetConsoleTextAttribute(h, 15);
		}
	} while (width % 2 == 0);

	cout << "Specify Kernel (" << height << "x" << width << ") : ";
	data = new float[width*height];

	for (int j = 0; j < height; j++)
	{
		for (int b = 0; b < width; b++)
		{
			cin >> data[j*width + b];
		}
	}

	return new Kernel(width, height, data);
}

Kernel::Kernel(unsigned char width, unsigned char height, float* data)
{
	this->width = width;
	this->height = height;
	this->data = data;
}

Kernel::~Kernel()
{
	if (data != nullptr)
	{
		delete data;
	}
}

void Kernel::print()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);

	cout << "Kernel  Width is: " << (int)width << endl;
	cout << "Kernel Height is: " << (int)height << endl;
	cout << "Kernel Data:" << endl;

	for (int j = 0; j < height; j++)
	{
		for (int b = 0; b < width; b++)
		{
			cout << fixed << setprecision(2) << data[j*width + b] << "\t";
		}
		cout << endl;
	}

	SetConsoleTextAttribute(h, 15);
}

Kernel* Kernel::getKernel()
{
	int option;
	cout << "Select Kernel:" << endl;
	cout << "\t 0 - own (specify)" << endl;
	cout << "\t 1 - Inedntity 9x9" << endl;
	cout << "\t 2 - Gausian blur 9x9" << endl;
	cout << "\t 3 - Sharpen 9x9" << endl;
	cout << "\t 4 - Edge Detection 9x9" << endl;

	cin >> option;

	switch (option) {
	case 1:
		return getIdentityKernel();
	case 2:
		return getGausianBlurKernel();
	case 3:
		return getSharpenKernel();
	case 4:
		return getEdgeDetectionKernel();
	default:
		return specifyKernel();
	}
	return nullptr;
}
