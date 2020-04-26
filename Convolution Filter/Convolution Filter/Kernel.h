#pragma once
class Kernel
{
private:
	unsigned char width;
	unsigned char height;
	float** data = nullptr;

public:
	Kernel(unsigned char width, unsigned char height, float** data);
	~Kernel();

	void print() const;
	inline unsigned char getWidth() const { return width; };
	inline unsigned char getHeight() const { return height; };
	inline float** getData() { return data; };
};

