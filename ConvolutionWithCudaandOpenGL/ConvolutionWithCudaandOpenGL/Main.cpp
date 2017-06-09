/**
  *
  * @author Jozef Blazicek
  * */

#include <windows.h>
#include <iomanip>
#include "Image.h"
#include "Kernel.h"
#include "Convolution.cuh"
#include "Window.h"

using namespace convolution_filter;

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 15);

	Image *image = Image::getImage();
	Kernel *kernel = Kernel::getKernel();
	kernel->print();

	Image * result = applyFilter(image, kernel);
	if (result == nullptr)
		return 1;
	Window window(result);
	window.display();

	return EXIT_SUCCESS;
}
