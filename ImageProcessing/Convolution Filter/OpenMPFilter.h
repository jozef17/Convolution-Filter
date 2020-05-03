#pragma once

#include "ConvolutionFilter.h"

class OpenMPFilter :
	public ConvolutionFilter
{
public:
	Image* applyFilter();

};
