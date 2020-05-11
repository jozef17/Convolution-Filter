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
	float Y, Cb, Cr;

	void toRGB();
	void toYCbCr();

public:

	Pixel(); // TODO
	Pixel(Pixel_T rgb);
	Pixel(float y, float cb, float cr);

	float getY() const;
	float getCb() const;
	float getCr() const;
	Pixel_T getRGB() const;

	void set(Pixel_T rgb);
	void set(float Y, float Cb, float Cr);

};

class Image
{
protected:
	std::vector<std::unique_ptr<Pixel>> data;

	unsigned int width = 0;
	unsigned int height = 0;

	Image();

public:
	Image(unsigned int width, unsigned int height);

	// Get Pixel Value
	Pixel_T get(unsigned int x, unsigned int y) const;
	float getY(unsigned int x, unsigned int y) const;
	float getCb(unsigned int x, unsigned int y) const;
	float getCr(unsigned int x, unsigned int y) const;

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	// Set pixel value
	void set(unsigned int x, unsigned int y, Pixel_T rgb);
	void set(unsigned int x, unsigned int y, float Y, float Cb, float Cr);

};

class RGBImage
	: public Image
{
public:
	RGBImage(unsigned int width, unsigned int height, std::string file);

};

class BMPImage
	: public Image
{
public:
	BMPImage(std::string file);

};
