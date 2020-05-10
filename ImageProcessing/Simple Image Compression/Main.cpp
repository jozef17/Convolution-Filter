#include "Window.h"
#include "ImageCompressor.h"
#include "Image.h"

#include <iostream>
#include <iomanip>

Image *getImage();
int getQuality();

int main()
{
	// Get Image
	Image *img = nullptr;
	while (img == nullptr)
		img = getImage();

	int quality = getQuality();

	float alpha = ImageCompressor::getAlpha(quality);
	Image *encoded = ImageCompressor::encode(*img, alpha);
	Image *decoded = ImageCompressor::decode(*encoded, alpha);

	delete img;
	delete encoded;

	Window w(decoded);
	w.display("Simple Image Compression");

	delete decoded;

	return 0;
}

Image *getImage()
{
	std::string filename;
	int width, height;

	std::cout << "Insert filename: ";
	std::cin >> filename;

	if (filename.at(filename.length() - 4) == '.' &&
		filename.at(filename.length() - 3) == 'b' &&
		filename.at(filename.length() - 2) == 'm' &&
		filename.at(filename.length() - 1) == 'p')
	{
		try 
		{
			return new BPMImage(filename);
		}
		catch (std::string s) 
		{
			std::cout << s << std::endl;
			return nullptr;
		}
	}
	else
	{
		std::cout << "Specify image height: ";
		std::cin >> height;
		std::cout << "Specfy image width:";
		std::cin >> width;

		return new RGBImage(width, height, filename);
	}
}

int getQuality()
{
	int quality;

	while (true) 
	{
		std::cout << "Specify result image quality (0% - 100%): ";
		std::cin >> quality;

		if ((quality >= 0) && (quality <= 100))
			return quality;
	}
}
