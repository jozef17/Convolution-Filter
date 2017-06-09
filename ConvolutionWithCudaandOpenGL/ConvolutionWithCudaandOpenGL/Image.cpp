/**
  *
  * @author Jozef Blazicek
  * */

#include "Image.h"
#include <fstream>
#include <iostream>

convolution_filter::Image::Image(int width, int height, std::string file) : imgWidth(width), imgHeight(height)
{
	data = new Pixel_t[width*height];
	std::ifstream in(file, std::ios::binary);
	in.read((char *)data, width * height * PIXEL_COMPONENT_COUNT);
	in.close();
}

convolution_filter::Image::~Image()
{
	if (data != nullptr)
		delete data;
}

convolution_filter::Image * convolution_filter::Image::getImage()
{
	std::string filename;
	int width, height;

	std::cout << "Insert filename: ";
	std::cin >> filename;
	std::cout << "Specify image height: ";
	std::cin >> height;
	std::cout << "Specfy image width:";
	std::cin >> width;

	return new Image(width, height, filename);
}
