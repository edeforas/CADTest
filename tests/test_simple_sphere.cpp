#include "BodyFactory.h"
#include "STLFile.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	BodyFactory::SphereGeodesic sphere(50);
	STLFile::save("simple_sphere.stl", sphere.mesh());
	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////