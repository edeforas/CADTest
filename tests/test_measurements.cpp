#include "BodyFactory.h"

#include "Mesh.h"
#include "MeshMeasurements.h"

#include <iostream>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Test Start." << endl;

	// test: is_closed()
	{
		BodyFactory::SphereUV sphere(1.);
		Mesh m = sphere.mesh();
		cout << "Orig Mesh is closed: " << MeshMeasurements::is_closed(m) << endl;

		for (int i = 0; i < m.nb_triangles(); i++)
		{
			if (rand() / (float)RAND_MAX > 0.5)
				m.unlink_triangle(i);
		}

		cout << "Mesh with holes is closed: " << MeshMeasurements::is_closed(m) << endl;
	}

	// test: volume() and surface()
	{
		double radius=1.;
		BodyFactory::SphereUV sphere(1.);
		sphere.set_mesh_precision(100);

		cout << "Mesh Volume: " << MeshMeasurements::volume(sphere.mesh()) << endl;
		cout << "Theorical Volume: " << 4. / 3. * 3.141592653 * (radius * radius * radius) << endl;
		cout << "Mesh Surface: " << MeshMeasurements::surface(sphere.mesh()) << endl;
		cout << "Theorical Surface: " << 4. * 3.141592653 * (radius * radius) << endl;
	}

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////