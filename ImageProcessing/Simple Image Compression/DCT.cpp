#include "DCT.h"
#include "Image.h"

#include <cmath>
#include <corecrt_math_defines.h>

// Calculates DCT for 8 by 8 block
void DCT::dctBlock(Image & in, Image & out, int xOffset, int yOffset)
{
	double sum[3];

	int M = (in.getWidth() - xOffset) > 8 ? 8 : in.getWidth() - xOffset;
	int N = (in.getHeight() - xOffset) > 8 ? 8 : in.getHeight() - xOffset;

	double f = (double)2.0 / std::sqrt((double)M * (double)N);

	// Loop at block
	for (int m = 0; m < M; m++)
	{
		for (int n = 0; n < N; n++)
		{
			// Clear sum
			for (char c = 0; c < 3; c++)
				sum[c] = 0;

			// Calculate Cos Sum
			for (int x = 0; x < M; x++)
			{
				for (int y = 0; y < N; y++)
				{
					double cos = std::cos(((2 * x + 1) * m * M_PI) / (2 * M)) * std::cos( ((2 * y + 1) * n * M_PI) / (2 * N));
					sum[0] += in.getY(xOffset + x, yOffset + y) * cos;
					sum[1] += in.getCb(xOffset + x, yOffset + y) * cos;
					sum[2] += in.getCr(xOffset + x, yOffset + y) * cos;
				}
			}

			double cm = m == 0 ? 1.0 / std::sqrt(2.0) : 1.0;
			double cn = n == 0 ? 1.0 / std::sqrt(2.0) : 1.0;

			sum[0] *= f * cm * cn;
			sum[1] *= f * cm * cn;
			sum[2] *= f * cm * cn;

			out.set(xOffset + m, yOffset + n, sum[0], sum[1], sum[2]);
		}
	}
}

// Calculates INverse DCT for 8 by 8 block
void DCT::idctBlock(Image & in, Image & out, int xOffset, int yOffset) 
{
	double sum[3];

	int M = (in.getWidth() - xOffset) > 8 ? 8 : in.getWidth() - xOffset;
	int N = (in.getHeight() - xOffset) > 8 ? 8 : in.getHeight() - xOffset;

	double f = (double)2.0 / std::sqrt((double)M * (double)N);

	// Loop at block
	for (int x = 0; x < M; x++)
	{
		for (int y = 0; y < N; y++)
		{
			// Clear sum
			for (char c = 0; c < 3; c++)
				sum[c] = 0;

			// Calculate Sum
			for (int m = 0; m < M; m++)
			{
				for (int n = 0; n < N; n++)
				{
					double cm = m == 0 ? 1.0 / std::sqrt(2) : 1.0;
					double cn = n == 0 ? 1.0 / std::sqrt(2) : 1.0;
					double cos = std::cos(((2 * x + 1) * m * M_PI) / (2 * M)) * std::cos(((2 * y + 1) * n * M_PI) / (2 * N));

					sum[0] += cm * cn * in.getY(xOffset + m, yOffset + n) * cos;
					sum[1] += cm * cn * in.getCb(xOffset + m, yOffset + n) * cos;
					sum[2] += cm * cn * in.getCr(xOffset + m, yOffset + n) * cos;
				}
			}

			// Multiply sum
			sum[0] *= f;
			sum[1] *= f;
			sum[2] *= f;

			out.set(xOffset + x, yOffset + y, sum[0], sum[1], sum[2]);
		}
	}
}

Image * DCT::dct(Image & image)
{
	Image *img = new Image(image.getWidth(), image.getHeight());

	for (unsigned int j = 0; j < image.getWidth(); j += 8)
	{
		for (unsigned int b = 0; b < image.getHeight(); b += 8)
		{
			// Process 8x8 blocks
			dctBlock(image, *img, j, b);
		}
	}

	return img;
}

Image * DCT::idct(Image & image)
{
	Image *img = new Image(image.getWidth(), image.getHeight());

	// Process 8x8 blocks
	for (unsigned int j = 0; j < image.getWidth(); j += 8)
	{
		for (unsigned int b = 0; b < image.getHeight(); b += 8)
		{
			// Process 8x8 blocks
			idctBlock(image, *img, j, b);
		}
	}

	return img;
}
