#pragma once

class Image;
class Kernel;

class ConvolutionFilter
{
private:
	Kernel *specifyKernel();

protected:
	Kernel *kernel = nullptr;
	Image *image = nullptr;

public:
	ConvolutionFilter();

	void setImage();

	void setKernel();

	virtual Image* applyFilter() = 0;

	~ConvolutionFilter();
};

