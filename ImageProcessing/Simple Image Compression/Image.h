#pragma once

#include <string>
#include <vector>
#include <memory>

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Pixel_T;

class Pixel
{
private:
	// RGB
	Pixel_T rgb;

	// YCbCe
	float Y;
	float Cb;
	float Cr;


	void toRGB();
	void toYCbCr();

public:

	Pixel(Pixel_T rgb);
	Pixel(float y, float cb, float cr);

	Pixel_T getRGB() const;

	float getY() const;
	float getCb() const;
	float getCr() const;

};

class Image
{
protected:
	std::vector<std::unique_ptr<Pixel>> data;
	//Pixel **data = nullptr;
	unsigned int width = 0;
	unsigned int height = 0;

	Image();

public:
//	Image(unsigned int width, unsigned int height, std::vector<std::unique_ptr<Pixel>> data);

	Pixel_T get(unsigned int x, unsigned int y);

	unsigned int getWidth();
	unsigned int getHeight();

};

class RGBImage
	: public Image
{
public:
	RGBImage(unsigned int width, unsigned int height, std::string file);

};

class BPMImage
	: public Image
{
public:
	BPMImage(std::string file);

};