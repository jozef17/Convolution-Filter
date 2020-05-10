#pragma once

class Image;

class ImageCompressor
{
public:	
	static float getAlpha(int quality);

	static Image * encode(Image &img, float alpha);

	static Image * decode(Image &img, float alpha);

};

