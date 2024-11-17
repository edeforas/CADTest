#include "MeshUtil.h"
#include "ImageUtil.h"

#include "Image.h"
#include "Mesh.h"

#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std; 

///////////////////////////////////////////////////////////////////////////
void MeshUtil::create_mesh_from_image(const Image& im, Mesh& m)
{
	m.clear();
	Image imBW;

	ImageUtil::convert_to_bw(im, imBW);

	for (int i = 0; i < imBW.width() - 1; i++)
		for (int j = 0; j < imBW.height() - 1; j++)
			m.add_quad(Point3(i, j, imBW(i, j)), Point3(i+1, j, imBW(i+1, j)), Point3(i + 1, j+1, imBW(i+1, j+1)), Point3(i , j+1, imBW(i, j+1)));
}
///////////////////////////////////////////////////////////////////////////

