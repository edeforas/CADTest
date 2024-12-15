#include "BodyFactory.h"
#include "STLFile.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	BodyFactory::SphereGeodesic sphere(50);
	STLFile::save("test_mesh_geosphere.stl", sphere.mesh());

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////