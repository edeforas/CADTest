#include <iostream>
using namespace std;

#include "Image.h"
#include "ImageGenerator.h"
#include "ImageIoBmp.h"

#include "MeshUtil.h"
#include "OBJFile.h"

////////////////////////////////////////////////////////////////////////////////
int main()
{
	//create a mesh using mandelbort set

	Image imgMandelbrot;
	ImageGenerator::Mandelbrot(imgMandelbrot, 256, 256,128);
	ImageIoBmp::write("test_mandelbrot_mesh.bmp", &imgMandelbrot);
	
	Mesh m;
	MeshUtil::create_mesh_from_image(imgMandelbrot, m);

	OBJFile::save("test_mandelbrot_mesh.obj", m);

	return 0;
}
////////////////////////////////////////////////////////////////////////////////
