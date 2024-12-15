#include "MeshFactory.h"
#include "STLFile.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	MeshFactory::SphereGeodesic sphere(50);
	STLFile::save("test_mesh_geosphere.stl", sphere.mesh());

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////