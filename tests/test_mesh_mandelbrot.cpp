#include <iostream>
using namespace std;

#include "Image.h"
#include "ImageGenerator.h"
#include "ImageIoBmp.h"

#include "Transform.h"
#include "MeshUtil.h"
#include "OBJFile.h"

////////////////////////////////////////////////////////////////////////////////
int main()
{
	//create a mesh using generated Mandelbrot set 

	Image imgMandelbrot;
	ImageGenerator::Mandelbrot(imgMandelbrot, 256, 256,128);
	ImageIoBmp::write("test_mesh_mandelbrot.bmp", &imgMandelbrot);
	
	Mesh m;
	MeshUtil::create_mesh_from_image(imgMandelbrot, m);
	m.apply_transform(Scale(1, 1, 0.3));

	//todo add base

	OBJFile::save("test_mesh_mandelbrot.obj", m);

	return 0;
}
////////////////////////////////////////////////////////////////////////////////
