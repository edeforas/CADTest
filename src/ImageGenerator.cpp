
#include "ImageGenerator.h"

namespace ImageGenerator
{
	///////////////////////////////////////////////////////////////////////////
	void Shierpinsky(Image &img,int iWidth,int iHeight)
	{
		img.resize(iWidth, iHeight, 4); // 32bpp
		for (int w = 0; w < img.width(); w++)
			for (int h = 0; h < img.height(); h++)
				*(int*)(img.pixel(w, h)) = ((w & h) == 0) * ((1 << 25) - 1); //Sierpinsky
		
	}
	///////////////////////////////////////////////////////////////////////////
	void Mandelbrot(Image& img, int iWidth, int iHeight, int iNbIteration) //slow pixel by pixel algorithm
	{
		float xmin = -2.1, xmax = 0.9;
		float ymin = -1.5, ymax = 1.5;

		img.resize(iWidth, iHeight, 4); // 32bpp

		for (int w = 0; w < img.width(); w++)
			for (int h = 0; h < img.height(); h++)
			{
				float cx = xmin + (img.width() - w) / (float)img.width() * (xmax - xmin);
				float cy = ymin + (img.height() - h) / (float)img.height() * (ymax - ymin);

				int iterMax = iNbIteration;

				float fx = cx;
				float fy = cy;
				
				// iterate
				while (fx * fx + fy * fy < 4.)
				{
					float fxy = fx*fy;
					fx = (fx + fy) * (fx - fy) + cx;
					fy = fxy + fxy + cy;

					if (iterMax == 0.)
						break;
					else
						iterMax--;
				}

				int color = (iNbIteration-iterMax) * (1*256*256 + 1*256 + 1); // todo nice color
				*((int*)img.pixel(w, h)) = color;
			}
	}
	///////////////////////////////////////////////////////////////////////////
}
