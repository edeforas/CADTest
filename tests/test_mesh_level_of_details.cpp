#include "MeshFactory.h"
#include "OBJFile.h"
#include "Transform.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	OBJWriter ow;
	ow.open("test_mesh_level_of_details.obj");
	Mesh m;

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating SphereUV with level of details=" << iLevel << endl;
		MeshFactory::create_sphere_uv(50,iLevel,m);
		m.apply_transform(Translation(Point3(120.*iLevel, 0., 0.)));
		ow.write(m);
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{	
		cout << "Generating Torus with level of details=" << iLevel << endl;
		MeshFactory::create_torus(30,20,iLevel,m);
		m.apply_transform(Translation(Point3(120.*iLevel, 120., 0.)));
		ow.write(m);
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating SphereGeodesic with level of details=" << iLevel << endl;
		MeshFactory::create_sphere_geodesic(50,iLevel,m);
		m.apply_transform(Translation(Point3(120.*iLevel, 240., 0.)));
		ow.write(m);
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating Cylinder with level of details=" << iLevel << endl;
		MeshFactory::create_cylinder(60.,40,iLevel,m);
		m.apply_transform(Translation(Point3(120. * iLevel, 360., 0.)));
		ow.write(m);
	}

	ow.close();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////