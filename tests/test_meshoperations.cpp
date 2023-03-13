#include "MeshFactory.h"
#include "MeshTessellate.h"
#include "STLFile.h"
#include "Mesh.h"
#include "MeshUtil.h"

#include <iostream>
#include <cstdlib>
using namespace std;

void test(bool a, const string& sMessage = "")
{
	if (a==false)
	{
		cerr << "Test Error: " << sMessage.c_str() << endl;
		exit(-1);
	}
}
///////////////////////////////////////////////////////////////////////////
void test_deleting_triangles()
{
	cout << endl << "test_deleting_triangles" << endl;

	// test triangles deleted
	Mesh m;
	MeshFactory::create_sphere_uv(100.,8,m);
	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (rand() / (float)RAND_MAX > 0.5)
			m.unlink_triangle(i);
	}

	bool bSaved = STLFile::save("test_deleting_triangles.stl", m);
	test(bSaved);
}
///////////////////////////////////////////////////////////////////////////
void test_vertices_merge()
{
	Mesh mi;
	MeshFactory::create_icosahedron(1.,mi);

	//create body with redondant vertices
	MeshTessellate mt;
	Mesh m;
	mt.compute(mi, 2, m);
	int iNbVerticeOld = m.nb_vertices();
	test(iNbVerticeOld == m.nb_triangles() * 3 ); //each triangle has 3 vertices

	MeshUtil::merge_vertices(m,1.e-5);
	int iNbVerticeNew = m.nb_vertices();

	test(iNbVerticeNew == 20 * 3 / 5 + 20 * 3 / 2);
}
///////////////////////////////////////////////////////////////////////////

void test_triangle_subdivision()
{
	Mesh m;
	cout << endl << "test_triangle_subdivision" << endl;
	// test triangles subdivision
	MeshFactory::create_sphere_geodesic(100.,8,m);

	// two scales split
	for (int iScale = 0; iScale < 2; iScale++)
	{
		int iNbTriangles = m.nb_triangles(); // only changing the old triangles, not the created 
		for (int i = 0; i < iNbTriangles; i++)
		{
			Point3 p1, p2, p3, vCenter;
			m.get_triangle_vertices(i, p1, p2, p3);

			int iNewVertex = m.add_vertex((p1 + p2 + p3) / 3.);
			m.split_triangle_with_vertex(i, iNewVertex);
		}
	}

	//renormalize all vertices
	for (int i = 0; i < m.nb_vertices(); i++)
	{
		Point3 v;
		m.get_vertex(i, v);
		m.set_vertex(i, v.normalized());
	}

	bool bSaved = STLFile::save("test_triangle_subdivision.stl", m);
	test(bSaved);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_deleting_triangles();
	test_vertices_merge();
	test_triangle_subdivision();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////