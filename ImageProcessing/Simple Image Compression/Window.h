#pragma once

#include <string>;

class Image;

class Window
{
private:
	Image *image;
	void *framebuffer = nullptr;
	int offset_x = 0;
	int offset_y = 0;

	void updateFramebuffer();

public:
	Window(Image *image);

	void move(int key, int action);
	void display(std::string name);

	~Window();
};
