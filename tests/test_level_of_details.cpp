#include "BodyFactory.h"
#include "OBJFile.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	OBJWriter ow;
	ow.open("test_level_of_details.obj");

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating SphereUV with level of details=" << iLevel << endl;
		BodyFactory::SphereUV sphere(50);
		sphere.set_mesh_precision(iLevel);
		sphere.transform().set_global_translation(Point3(120.*iLevel, 0., 0.));
		ow.write(sphere.mesh());
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating Torus with level of details=" << iLevel << endl;
		BodyFactory::Torus torus(30,20);
		torus.set_mesh_precision(iLevel);
		torus.transform().set_global_translation(Point3(120.*iLevel, 120., 0.));
		ow.write(torus.mesh());
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating SphereGeodesic with level of details=" << iLevel << endl;
		BodyFactory::SphereGeodesic sphere(50);
		sphere.set_mesh_precision(iLevel);
		sphere.transform().set_global_translation(Point3(120.*iLevel, 240., 0.));
		ow.write(sphere.mesh());
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating Cylinder with level of details=" << iLevel << endl;
		BodyFactory::Cylinder cylinder(60.,40);
		cylinder.set_mesh_precision(iLevel);
		cylinder.transform().set_global_translation(Point3(120. * iLevel, 360., 0.));
		ow.write(cylinder.mesh());
	}

	ow.close();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////