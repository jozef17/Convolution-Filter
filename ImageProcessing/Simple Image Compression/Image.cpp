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

Pixel::Pixel() : rgb{ 0,0,0 }, Y(0.0), Cb(0.0), Cr(0.0) {}

Pixel::Pixel(Pixel_T rgb) : rgb(rgb)
{
	toYCbCr();
}

Pixel::Pixel(float y, float cb, float cr) : Y(y), Cb(cb), Cr(cr)
{
	toRGB();
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

Pixel_T Pixel::getRGB() const
{
	return rgb;
}

void Pixel::set(Pixel_T rgb)
{
	this->rgb = rgb;
	toYCbCr();
}

void Pixel::set(float Y, float Cb, float Cr)
{
	this->Y = Y;
	this->Cb = Cb;
	this->Cr = Cr;
	toRGB();
}


Image::Image() { }

Image::Image(unsigned int width, unsigned int height) : width(width), height(height)
{

	int b = 0;
	data.resize(width * height);

	for (unsigned int j = 0; j < width * height; j++) {
		data[b++] = std::make_unique<Pixel>();
	}
}

Pixel_T Image::get(unsigned int y, unsigned int x)  const
{
	if ((x >= width) || (y >= height))
		return Pixel_T();

	return data[y * width + x]->getRGB();
}

float Image::getY(unsigned int x, unsigned int y)  const
{
	if ((x >= width) || (y >= height))
		return -1;

	return data[y * width + x]->getY();
}

float Image::getCb(unsigned int x, unsigned int y)  const
{
	if ((x >= width) || (y >= height))
		return -1;

	return data[y * width + x]->getCb();

}

float Image::getCr(unsigned int x, unsigned int y)  const
{
	if ((x >= width) || (y >= height))
		return -1;

	return data[y * width + x]->getCr();

}

unsigned int Image::getWidth() const
{
	return width;
}

unsigned int Image::getHeight() const
{
	return height;
}

void Image::set(unsigned int x, unsigned int y, Pixel_T rgb)
{
	if ((x >= width) || (y >= height))
		return;

	data[y * width + x]->set(rgb);
}

void Image::set(unsigned int x, unsigned int y, float Y, float Cb, float Cr)
{
	if ((x >= width) || (y >= height))
		return;

	data[y * width + x]->set(Y, Cb, Cr);
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
