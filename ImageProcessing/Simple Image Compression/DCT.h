#pragma once

class Image;

class DCT
{
private:
	// Calculate dct for 8 by 8 block
	static void dctBlock(Image &in, Image &out, int xOffset, int yOffset);

	// Calculate idct for 8 by 8 block
	static void idctBlock(Image & in, Image & out, int xOffset, int yOffset);

public:

	// Applies Discrete Cosine Transformation to image
	static Image *dct(Image &image);

	// Applies Inverse Discrete Cosine Transformation to image
	static Image *idct(Image &image);

};

