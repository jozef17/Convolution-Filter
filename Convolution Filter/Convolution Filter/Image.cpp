#include "Image.h"

#include <fstream>

Image::Image(int width, int height, std::string file) : imgWidth(width), imgHeight(height)
{
	data = new Pixel_t[width*height];
	std::ifstream in(file, std::ios::binary);
	in.read((char *)data, width * height * 3);
	in.close();
}

Image::Image(int width, int height, Pixel_t *data) : imgWidth(width), imgHeight(height), data(data) {};

Image::~Image()
{
	if (data != nullptr)
		delete data;
}
