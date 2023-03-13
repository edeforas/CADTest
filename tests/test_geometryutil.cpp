#include "GeometryUtil.h"
#include "Mesh.h"
#include "STLFile.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
void test_geometryutil_sphere_random_triangles()
{
	//create sphere filled with random triangles in a ribbon
	Mesh m;
	Point3 p;
	int iRibbonSize = 200;

	GeometryUtil::compute_random_axis(p);
	m.add_vertex(p);
	GeometryUtil::compute_random_axis(p);
	m.add_vertex(p);

	for (int i = 2; i < iRibbonSize; i++)
	{
		GeometryUtil::compute_random_axis(p, i);
		m.add_vertex(p);

		m.add_triangle(i, i - 1, i - 2);
	}

	//close ribbon
	m.add_triangle(iRibbonSize-2, iRibbonSize-1, 0);
	m.add_triangle(iRibbonSize-1, 0, 1);


	STLFile::save("test_geometryutil_sphere_random_triangles.stl", m);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Tests start..." << endl;

	test_geometryutil_sphere_random_triangles();

	cout << "Tests finished." << endl;
	return 0;
}