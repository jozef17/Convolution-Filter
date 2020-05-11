#include "Kernel.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <iomanip>

Kernel::Kernel(unsigned char width, unsigned char height, float** data) : width(width), height(height), data(data) {}

Kernel::~Kernel()
{
	if (data != nullptr)
	{
		for (int i = 0; i < height; i++)
			if (data[i] != nullptr)
				delete data[i];
		delete data;
	}
}

void Kernel::print() const
{
#ifdef _WIN32
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);
#endif
	std::cout << "Kernel Width is:  " << (int)width << std::endl;
	std::cout << "Kernel Height is: " << (int)height << std::endl;
	std::cout << "Kernel Data:" << std::endl;

	for (int j = 0; j < height; j++)
	{
		std::cout << "\t";
		for (int b = 0; b < width; b++)
		{
			std::cout << std::fixed << std::setprecision(2) << data[j][b] << "\t";
		}
		std::cout << std::endl;
	}
#ifdef _WIN32
	SetConsoleTextAttribute(h, 15);
#endif
}
