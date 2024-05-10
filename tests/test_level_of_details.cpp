#include "BodyFactory.h"
#include "OBJFile.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	Mesh m,mTotal;

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating SphereUV with level of details=" << iLevel << endl;
		BodyFactory::SphereUV sphere(50);
		sphere.set_mesh_precision(iLevel);
		sphere.transform().set_global_translation(Point3(120.*iLevel, 0., 0.));
		mTotal.add_mesh(sphere.mesh());
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating Torus with level of details=" << iLevel << endl;
		BodyFactory::Torus torus(30,20);
		torus.set_mesh_precision(iLevel);
		torus.transform().set_global_translation(Point3(120.*iLevel, 120., 0.));
		mTotal.add_mesh(torus.mesh());
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating SphereGeodesic with level of details=" << iLevel << endl;
		BodyFactory::SphereGeodesic sphere(50);
		sphere.set_mesh_precision(iLevel);
		sphere.transform().set_global_translation(Point3(120.*iLevel, 240., 0.));
		mTotal.add_mesh(sphere.mesh());
	}

	for (int iLevel = 1; iLevel < 10; iLevel++)
	{
		cout << "Generating Cylinder with level of details=" << iLevel << endl;
		BodyFactory::Cylinder cylinder(60.,50.);
		cylinder.set_mesh_precision(iLevel);
		cylinder.transform().set_global_translation(Point3(120. * iLevel, 360., 0.));
		mTotal.add_mesh(cylinder.mesh());
	}

	cout << "Saving: level_of_details.obj" << endl;
	OBJFile::save("level_of_details.obj", mTotal);

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////