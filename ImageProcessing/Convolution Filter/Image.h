#pragma once

#include <string>

typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Pixel_t;

class Image
{
private:
	int imgWidth = 0;
	int imgHeight = 0;
	Pixel_t* data = nullptr;

public:
	// Loads image from file
	Image(int width, int height, std::string file);

	Image(int width, int height, Pixel_t *data);

	~Image();

	inline int getWidth() const { return imgWidth; };
	inline int getHeight() const { return imgHeight; };

	// Get & Set Pixel value at y,x
	inline Pixel_t get(int y, int x) const { return data[y * imgWidth + x]; };
	inline void set(int y, int x, Pixel_t val) { data[y*imgWidth + x] = val; };
};

