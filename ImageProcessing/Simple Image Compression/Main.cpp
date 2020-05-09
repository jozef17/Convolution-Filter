#include "Image.h"
#include "Window.h"

#include "DCT.h"

#include <iostream>
#include <iomanip>

int main()
{
	// Original Image
	Image *dct = new Image(8, 8);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			unsigned char X;
			if (i % 2 == 0)
				X = (unsigned char)(((i % 2) * 255) + (j % 2) * 255);
			else
				X = j % 2 == 0 ? 255 : 0;

			std::cout <<(int) X  << " ";
			dct->set(i, j, (float)X, 0, 0);
		}
	}
	std::cout << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	// DCT
	Image *dctRes = DCT::dct(*dct);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			std::cout << (int) dctRes->getY(i, j) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "------------------------------------------" << std::endl;

	// IDCT
	Image *idctRes = DCT::idct(*dctRes);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			std::cout << (int)idctRes->getY(i, j) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	delete dct;
	delete dctRes;
	delete idctRes;

//	Image *i = new BPMImage("C:\\Image.bmp");
//	Window *w = new Window(i);
//	w->display("Test");

//	delete i;
//	delete w;

	return 0;
}