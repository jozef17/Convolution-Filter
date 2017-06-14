/**
  *
  * @author Jozef Blazicek
  * */

#include <GLFW/glfw3.h>
#include "Window.h"

convolution_filter::Window *window = nullptr;

void keyCallback(GLFWwindow *, int key, int, int action, int)
{
	if (window != nullptr)
		window->move(key, action);
}

// Copy to framebuffer part of image to be displayed
void convolution_filter::Window::updateFramebuffer()
{
	int index = WIDTH*HEIGHT - 1;
	Pixel_t *data = image->getData();
	int imageWidth = image->getWidth();

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int b = WIDTH - 1; b >= 0; b--)
		{
			framebuffer[index].red = data[(j + offset_y) * imageWidth + b + offset_x].red;
			framebuffer[index].green = data[(j + offset_y) * imageWidth + b + offset_x].green;
			framebuffer[index].blue = data[(j + offset_y) * imageWidth + b + offset_x].blue;
			index--;
		}
	}
}

// Handle user input - move image
void convolution_filter::Window::move(int key, int action)
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

void convolution_filter::Window::display()
{
	// Create Window
	window = this;
	updateFramebuffer();

	GLFWwindow* window;

	if (!glfwInit())
	{
		return;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Convolution filter", NULL, NULL);

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