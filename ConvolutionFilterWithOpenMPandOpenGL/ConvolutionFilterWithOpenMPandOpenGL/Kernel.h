/**
 *
 * @author Jozef Blazicek
 * */

#ifndef BLAZICEK_CONVOLUTION_KERNEL
#define BLAZICEK_CONVOLUTION_KERNEL

namespace convolution_filter
{

	class Kernel
	{
	private:
		unsigned char width;
		unsigned char height;
		float** data = nullptr;

		static Kernel* getIdentityKernel();
		static Kernel* getGausianBlurKernel();
		static Kernel* getSharpenKernel();
		static Kernel* getEdgeDetectionKernel();
		static Kernel* specifyKernel();
	public:
		Kernel(unsigned char width, unsigned char height, float** data);
		~Kernel();

		void print();
		inline unsigned char getWidth() { return width; };
		inline unsigned char getHeight() { return height; };
		inline float** getData() { return data; };

		static Kernel* getKernel();
	};

}
#endif
