#include "BodyFactory.h"
#include "STLFile.h"
#include "Mesh.h"

#include <iostream>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Test Start." << endl;

	{
		// test triangles deleted
		BodyFactory::SphereUV sphere(100.);
		Mesh m=sphere.mesh();
		for (int i = 0; i < m.nb_triangles(); i++)
		{
			if (rand() / (float)RAND_MAX > 0.5)
				m.unlink_triangle(i);
		}

		if (!STLFile::save("sphere_triangles_deleted.stl", m))
		{
			cout << "Unable to write sphere_triangles_deleted.stl, good path and rights ? " << endl;
			return -1;
		}
	}

	{
		// test triangles subdivision
		BodyFactory::SphereGeodesic sphere(100.);
		Mesh m=sphere.mesh();

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
			m.get_vertex(i,v);
			m.set_vertex(i, v.normalized());
		}

		if (!STLFile::save("sphere_triangles_subdiv.stl", m))
		{
			cout << "Unable to write sphere_triangles_subdiv.stl, good path and rights ? " << endl;
			return -1;
		}
	}

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////