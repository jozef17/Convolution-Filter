/**
  *
  * @author Jozef Blazicek
  * */

#include <windows.h>
#include <iomanip>
#include "Convolution.h"
#include "Image.h"
#include "Window.h"

using namespace convolution_filter;

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);

	Convolution *convolution = new Convolution();
	convolution->setImage();
	convolution->setKernel();
	Image *resultImage = convolution->applyFilter();
	delete convolution;

	if (resultImage == nullptr)
		return EXIT_FAILURE;

	Window w(resultImage);
	w.display();

	return EXIT_SUCCESS;
}
