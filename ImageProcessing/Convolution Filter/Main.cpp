/**
  * Entry point of program
  *
  * @author Jozef Blazicek
  * */
#define STD

#include <stdlib.h>
#include <chrono>
#include <iostream>
#include "Window.h"

#if defined( CUDA )
// USe cuda
#include "CudaFilter.cuh"
#elif defined ( OPEN_MP )
// Use OprnMP
#include "OpenMPFilter.h"
#elif defined ( STD )
// Use std::thread
#include "StdFilter.h"
#endif

ConvolutionFilter * getFilter();

int main()
{
	ConvolutionFilter * filter = getFilter();

	// Set image and Kernel
	filter->setImage();
	filter->setKernel();

	// Apply filter and measure how long it took
	std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
	Image *resultImage = filter->applyFilter();
	std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();

	// Cleanup
	delete filter;

	if (resultImage == nullptr)
		return EXIT_FAILURE;

	// Write duraton staticstics
	std::cout << "Convolution time: " << (endTime - startTime).count() << "s" << std::endl;

	// Display Result image
	Window w(resultImage);
	w.display();

	// Cleanup & exit
	delete resultImage;
	return EXIT_SUCCESS;
}

ConvolutionFilter * getFilter()
{
#if defined( CUDA )
	return new CudaFilter();
#elif defined ( OPEN_MP )
	return new OpenMPFilter();
#elif defined ( STD )
	return new StdFilter();
#endif
}
