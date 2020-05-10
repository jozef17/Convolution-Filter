#include "ImageCompressor.h"
#include "DCT.h"
#include "Image.h"

// Quantization tables
static const unsigned char QL[8][8] = { { 16, 11, 10, 16,  24,  40,  51,  61 },
										{ 12, 12, 14, 19,  26,  58,  60,  55 },
										{ 14, 13, 16, 24,  40,  57,  69,  56 },
										{ 14, 17, 22, 29,  51,  87,  80,  62 },
										{ 18, 22, 37, 56,  68, 109, 103,  77 },
										{ 24, 35, 55, 64,  81, 104, 113,  92 },
										{ 49, 64, 78, 87, 103, 121, 120, 101 },
										{ 72, 92, 95, 98, 112, 100, 103,  99 } };

static const unsigned char QC[8][8] = { { 17, 18, 24, 47, 99, 99, 99, 99 },
										{ 18, 21, 26, 66, 99, 99, 99, 99 },
										{ 24, 26, 56, 99, 99, 99, 99, 99 },
										{ 47, 66, 99, 99, 99, 99, 99, 99 },
										{ 99, 99, 99, 99, 99, 99, 99, 99 },
										{ 99, 99, 99, 99, 99, 99, 99, 99 },
										{ 99, 99, 99, 99, 99, 99, 99, 99 },
										{ 99, 99, 99, 99, 99, 99, 99, 99 } };

float ImageCompressor::getAlpha(int quality)
{
	if (quality < 50)
		return 50.0f / (float)quality;
	return 2.0f - (float)quality / 50.0f;
}

Image * ImageCompressor::encode(Image &img, float alpha)
{
	Image * res = DCT::dct(img);

	// Process 8 by 8 blocks
	for (unsigned int j = 0; j < img.getWidth(); j += 8)
	{
		for (unsigned int b = 0; b < img.getHeight(); b += 8)
		{
			int M = (img.getWidth() - j) > 8 ? 8 : img.getWidth() - j;
			int N = (img.getHeight() - b) > 8 ? 8 : img.getHeight() - b;

			// Process Block
			for (int x = 0; x < M; x++)
			{
				for (int y = 0; y < N; y++)
				{
					float Y = std::round(res->getY(j + x, b + y) / (alpha * QL[x][y]));
					float Cb = std::round(res->getCb(j + x, b + y) / (alpha * QC[x][y]));
					float Cr = std::round(res->getCr(j + x, b + y) / (alpha * QC[x][y]));

					res->set(j + x, b + y, Y, Cb, Cr);
				} // y
			} // x

		}// b
	}// j

	return res;
}

Image * ImageCompressor::decode(Image &img, float alpha)
{
	Image tmp(img.getWidth(), img.getHeight());

	for (unsigned int j = 0; j < img.getWidth(); j += 8)
	{
		for (unsigned int b = 0; b < img.getHeight(); b += 8)
		{
			int M = (img.getWidth() - j) > 8 ? 8 : img.getWidth() - j;
			int N = (img.getHeight() - b) > 8 ? 8 : img.getHeight() - b;

			// Process Block
			for (int x = 0; x < M; x++)
			{
				for (int y = 0; y < N; y++)
				{
					float Y = img.getY(j + x, b + y) * (alpha * QL[x][y]);
					float Cb = img.getCb(j + x, b + y) * (alpha * QC[x][y]);
					float Cr = img.getCr(j + x, b + y) * (alpha * QC[x][y]);

					tmp.set(j + x, b + y, Y, Cb, Cr);
				} // y
			} // x

		}
	}

	return DCT::idct(tmp);
}
