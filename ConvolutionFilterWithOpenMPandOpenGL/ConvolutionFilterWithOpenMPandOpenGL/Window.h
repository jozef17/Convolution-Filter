/**
  *
  * @author Jozef Blazicek
  * */

#ifndef BLAZICEK_CONVOLUTION_WINDOW
#define BLAZICEK_CONVOLUTION_WINDOW

#include <GLFW/glfw3.h>
#include "Image.h"

#define WIDTH 512
#define HEIGHT 512

namespace convolution_filter
{

	class Window
	{
	private:
		Image *image;
		Pixel_t framebuffer[WIDTH * HEIGHT];
		int offset_x = 0;
		int offset_y = 0;

		void updateFramebuffer();
	public:
		Window(Image *image) : image(image) {};

		void move(int key, int action);
		void display();
	};

}
#endif
