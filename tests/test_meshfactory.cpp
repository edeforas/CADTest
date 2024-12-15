#include "MeshFactory.h"
#include "Mesh.h"
#include "OBJFile.h"

///////////////////////////////////////////////////////////////////////////
int main()
{
	OBJWriter ow;
	ow.open("test_meshfactory.obj");

	Mesh m;
	MeshFactory::create_tetrahedron(25.,m);
	ow.write(m);

	MeshFactory::create_box(40., 50., 60., m);
	m.apply_transform(Translation(Point3(100., 0., 0.)));
	ow.write(m);

	MeshFactory::Cylinder cylinder(60., 30.);
	cylinder.transform().set_global_translation(Point3(200., 0., 0.));
	ow.write(cylinder.mesh());

	MeshFactory::Octahedron octahedron(40.);
	octahedron.transform().set_global_translation(Point3(0., 100., 0.));
	ow.write(octahedron.mesh());

	MeshFactory::Dodecahedron dodecahedron(20.);
	dodecahedron.transform().set_global_translation(Point3(100., 100., 0.));
	ow.write(dodecahedron.mesh());

	MeshFactory::Icosahedron icosahedron(30.);
	icosahedron.transform().set_global_translation(Point3(200, 100, 0.));
	ow.write(icosahedron.mesh());

	MeshFactory::SphereUV sphereUV(30.);
	sphereUV.transform().set_global_translation(Point3(0., 200., 0));
	ow.write(sphereUV.mesh());

	MeshFactory::SphereGeodesic sphereGeo(30.);
	sphereGeo.transform().set_global_translation(Point3(100., 200., 0));
	ow.write(sphereGeo.mesh());

	MeshFactory::Torus torus(25.,10.);
	torus.transform().set_global_translation(Point3(200., 200., 0.));
	ow.write(torus.mesh());

	ow.close();
	return 0;
}
///////////////////////////////////////////////////////////////////////////