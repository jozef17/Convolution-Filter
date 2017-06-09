/**
  *
  * @author Jozef Blazicek
  * */

#ifndef BLAZICEK_IMAGE
#define BLAZICEK_IMAGE

#include <string>

#define PIXEL_COMPONENT_COUNT 3

namespace convolution_filter
{

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

		Image(int width, int height, std::string file);
	public:
		Image(int width, int height, Pixel_t *data) : imgWidth(width), imgHeight(height), data(data) {};
		~Image();

		int getWidth() { return imgWidth; };
		int getHeight() { return imgHeight; };
		inline Pixel_t* getData() { return data; };
		void setWidth(int w) { imgWidth = w; };

		static Image* getImage();
	};

}
#endif
