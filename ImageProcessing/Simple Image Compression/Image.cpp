#include "Image.h"

#include <fstream>
#include <Windows.h>
#include <wingdi.h>

void Pixel::toRGB()
{
	rgb.red = 1.164 * (Y - 16) + 1.596 * (Cr - 128);
	rgb.green = 1.164 * (Y - 16) - 0.813 * (Cr - 128) - 0.392 * (Cb - 128);
	rgb.blue = 1.164 * (Y - 16) + 2.017 * (Cb - 128);
}

void Pixel::toYCbCr()
{
	Y = 0.257 * rgb.red + 0.504 * rgb.green + 0.098 * rgb.blue + 16;
	Cb = -0.148 * rgb.red - 0.291 * rgb.green + 0.439 * rgb.blue + 128;
	Cr = 0.439 * rgb.red - 0.368 * rgb.green - 0.071 * rgb.blue + 128;
}

Pixel::Pixel(Pixel_T rgb) : rgb(rgb)
{
	toYCbCr();
}

Pixel::Pixel(float y, float cb, float cr) : Y(y), Cb(cb), Cr(cr)
{
	toRGB();
}

Pixel_T Pixel::getRGB() const
{
	return rgb;
}

float Pixel::getY() const
{
	return Y;
}

float Pixel::getCb() const
{
	return Cb;
}

float Pixel::getCr() const
{
	return Cr;
}



Image::Image() { }

//Image::Image(unsigned int width, unsigned int height, std::vector<std::unique_ptr<Pixel>> data) : width(width), height(height), data(data) { }

Pixel_T Image::get(unsigned int y, unsigned int x)
{
	if ((x >= width) || (y >= height))
		return Pixel_T();

	return data[y * width + x]->getRGB();
}

unsigned int Image::getWidth()
{
	return width;
}

unsigned int Image::getHeight()
{
	return height;
}



RGBImage::RGBImage(unsigned int width, unsigned int height, std::string file)
{
	data.resize(width * height);
	Pixel_T *rawData = new Pixel_T[width * height];
	std::ifstream in(file, std::ios::binary);
	in.read((char *)rawData, width * height * 3);
	in.close();

	for (unsigned int j = 0; j < width * height; j++)
	{
		data[j] = std::make_unique<Pixel>(rawData[j]);
	}

	delete rawData;
}

BPMImage::BPMImage(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	// TODO file exists ???

	BITMAPFILEHEADER *bmpHeader = (BITMAPFILEHEADER *)new unsigned char[sizeof(BITMAPFILEHEADER)];
	BITMAPINFOHEADER *bmpInfo = (BITMAPINFOHEADER *)new unsigned char[sizeof(BITMAPINFOHEADER)];; // Info 

	file.read((char *)bmpHeader, sizeof(BITMAPFILEHEADER));
	file.read((char *)bmpInfo, sizeof(BITMAPINFOHEADER));

	// TODO BPM check bmpHeader->bfType == 0x4D42

	this->height = bmpInfo->biHeight;
	this->width = bmpInfo->biWidth;

	unsigned long offset = bmpHeader->bfOffBits;
	unsigned long size = bmpInfo->biSizeImage;

	// Cleanup (no longer needed)
	delete bmpHeader;
	delete bmpInfo;

	unsigned char *buffer = new unsigned char[size];

	file.seekg(offset); // go to start of data
	file.read((char*)buffer, size); // read data

	unsigned int b = 0;
	data.resize(width * height);
	for (unsigned int j = 0; j < size; j += 3) {
		Pixel_T pixel{ buffer[j + 2],buffer[j + 1], buffer[j] };
		data[b++] = std::make_unique<Pixel>(pixel);
	}

}
