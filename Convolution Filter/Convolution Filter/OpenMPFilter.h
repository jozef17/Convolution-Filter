#pragma once
#include "ConvolutionFilter.h"

class OpenMPFilter :
	public ConvolutionFilter
{
public:
	OpenMPFilter() : ConvolutionFilter() {};

	Image* applyFilter();
};
