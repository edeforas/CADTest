#ifndef _ImageGenerator_
#define _ImageGenerator_

#include "Image.h"

namespace ImageGenerator
{
	void Shierpinsky(Image &img,int iWidth,int iHeight);
	void Mandelbrot(Image& img, int iWidth, int iHeight, int iNbIter=255);
	
}

#endif
