#pragma once

#include "ConvolutionFilter.h"

class StdFilter :
	public ConvolutionFilter
{
public:
	Image* applyFilter();

};
