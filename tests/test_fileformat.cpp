#include "MeshFactory.h"

#include "STLFile.h"
#include "OBJFile.h"

///////////////////////////////////////////////////////////////////////////
int main()
{
	// build object
	MeshFactory::Cylinder cylinder(100., 40.);

	//test save
	STLFile::save("cylinder.stl", cylinder.mesh());
	OBJFile::save("cylinder.obj", cylinder.mesh());

	//test load and save stl
	Mesh m1;
	STLFile::load("cylinder.stl", m1);
	STLFile::save("cylinder.stl", m1);

	//test load and save obj
	Mesh m2;
	OBJFile::load("cylinder.obj", m2);
	OBJFile::save("cylinder.obj", m2);

	return 0;
}
///////////////////////////////////////////////////////////////////////////