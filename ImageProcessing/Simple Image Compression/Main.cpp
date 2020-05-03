#include "Image.h"
#include "Window.h"

int main()
{
	// bpm image loading test
	Image *i = new BPMImage("C:\\Image.bmp");
	Window *w = new Window(i);
	w->display("Test");

	return 0;
}