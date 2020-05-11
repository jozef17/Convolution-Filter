#include "Window.h"

#include <GLFW/glfw3.h>
#include "Image.h"

#define WIDTH 512
#define HEIGHT 512

Window *window = nullptr;

void keyCallback(GLFWwindow *, int key, int, int action, int)
{
	if (window != nullptr)
		window->move(key, action);
}

// Copy to framebuffer part of image to be displayed
void Window::updateFramebuffer()
{
	int index = WIDTH * HEIGHT - 1;
	int imageWidth = image->getWidth();

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int b = WIDTH - 1; b >= 0; b--)
		{
			Pixel_T pixel = image->get(j + offset_y, b + offset_x);
			((Pixel_T *)framebuffer)[index--] = pixel;
		}
	}
}

Window::Window(Image *image) : image(image)
{
	framebuffer = new Pixel_T[WIDTH * HEIGHT];
}

// Handle user input - move image
void Window::move(int key, int action)
{
	switch (key)
	{
	case GLFW_KEY_LEFT:
		offset_x = (offset_x - 1) >= 0 ? offset_x - 1 : 0;
		break;
	case GLFW_KEY_RIGHT:
		offset_x = (offset_x + 1) < (image->getWidth() - WIDTH) ? offset_x + 1 : image->getWidth() - WIDTH;
		break;
	case GLFW_KEY_UP:
		offset_y = (offset_y - 1) >= 0 ? offset_y - 1 : 0;
		break;
	case GLFW_KEY_DOWN:
		offset_y = (offset_y + 1) < (image->getHeight() - HEIGHT) ? offset_y + 1 : image->getHeight() - HEIGHT;
		break;
	}
	updateFramebuffer();
}

void Window::display(std::string name)
{
	// Create Window
	window = this;
	updateFramebuffer();

	GLFWwindow* window;

	if (!glfwInit())
	{
		return;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), NULL, NULL);

	if (window == NULL)
	{
		glfwTerminate();
		return;
	}

	// Setting callback
	glfwSetKeyCallback(window, keyCallback);
	glfwMakeContextCurrent(window);

	// Displaying framebuffer
	while (!glfwWindowShouldClose(window))
	{
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);

		glViewport(0, 0, WIDTH, HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();
}

Window::~Window()
{
	if (framebuffer != nullptr)
		delete framebuffer;
}
