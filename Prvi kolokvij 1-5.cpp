#include<iostream>
#include<cstdlib>
#include<ctime>
class Image
{
	int width, height, bytePerPixel;
public:
	Image():width(0),height(0),bytePerPixel(0){}
	Image(int width, int height, int bytePerPixel) :width(width), height(height), bytePerPixel(bytePerPixel){}
	void setwidth(int);
	void setheight(int);
	void setbytePerPixel(int);
	int getwidth() const;
	int getheight() const;
	int getbytePerPixel() const;
	void scaling(float);
	int getSizeKB();
	int getSizeKB(float);

};
void Image::setwidth(int width)
{
	this->width = width;
}
void Image::setheight(int height)
{
	this->height = height;
}
void Image::setbytePerPixel(int bytePerPixel)
{
	this->bytePerPixel = bytePerPixel;
}
int Image::getwidth() const
{
	return width;
}
int Image::getheight() const
{
	return height;
}
int Image::getbytePerPixel() const
{
	return bytePerPixel;
}
void Image::scaling(float sc)
{
	if (sc > 0.1)
	{
		width *= sc;
		height *= sc;
	}
}
int Image::getSizeKB()
{
	return (width * height * bytePerPixel)/1024;
}
int Image::getSizeKB(float compression)
{
	if (compression > 10.0 && compression < 90.0)
		return (width * height * bytePerPixel * compression/100)/1024;
	else
		return 0;
}
bool checkIfFits(Image* polje, int n,int sizeKB)
{
	int maxKB=0;
	for (int i = 0; i < n; i++)
	{
		if (polje[i].getSizeKB() > maxKB)
			maxKB = polje[i].getSizeKB();
	}
	if (maxKB < sizeKB)
		return 1;
	else
		return 0;
}

int main()
{
	srand(time(NULL));
	float compressPercentage = 75.2;
	Image lena(1024, 1024, 3), anna;
	std::cout << "Size:" << lena.getSizeKB() << ", compressed: " << lena.getSizeKB(compressPercentage) << std::endl;
	Image values[10];
	for (int i = 0; i < 10; i++)
	{
		values[i] = Image(rand() % 4000+1, rand() % 3000+1, rand() % 5+1);
	}
	if (checkIfFits(values, 10, 13588))
		std::cout << "Najveca slika u polju moze se pohraniti" << std::endl;
	else
		std::cout << "Najveca slika u polju ne moze se pohraniti" << std::endl;
	return 0;
}