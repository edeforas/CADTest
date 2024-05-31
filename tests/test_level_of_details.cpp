#include "BodyFactory.h"
#include "OBJFile.h"
#include "Mesh.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
	Mesh m,mTotal;

	for (int iLevel = 2; iLevel < 7; iLevel++)
	{
		cout << "Generating sphere with level of details=" << iLevel << endl;
		BodyFactory::SphereUV sphere(50); // for now; sphereUV, will be replaced by SphereGeodesic
		sphere.set_mesh_precision(2<<iLevel);
		sphere.transform().set_global_translation(Point3(120.*iLevel, 0., 0.));
		mTotal.add_mesh(sphere.mesh());
	}

	cout << "Saving: spheres_level_of_details.obj" << endl;
	OBJFile::save("spheres_level_of_details.obj", mTotal);

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////