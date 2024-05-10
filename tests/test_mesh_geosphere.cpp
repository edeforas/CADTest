#include "MeshFactory.h"
#include "STLFile.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	Mesh m;
	MeshFactory::create_sphere_geodesic(50,8,m);
	STLFile::save("test_mesh_geosphere.stl", m);

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////