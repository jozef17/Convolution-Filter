/**
  *
  * @author Jozef Blazicek
  * */

#ifndef BLAZICEK_CONVOLUTION
#define BLAZICEK_CONVOLUTION

#include <string>
#include "Image.h"
#include "Kernel.h"

namespace convolution_filter {

	class Convolution {
	private:
		Kernel *kernel = nullptr;
		Image *image = nullptr;
	public:
		~Convolution();

		void setImage();
		void setKernel();
		Image *applyFilter();
	};

}
#endif
