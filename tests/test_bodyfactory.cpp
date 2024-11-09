#include "BodyFactory.h"
#include "Mesh.h"
#include "OBJFile.h"

///////////////////////////////////////////////////////////////////////////
int main()
{
	
	OBJWriter ow;
	ow.open("test_body_factory.obj");

	BodyFactory::Tetrahedron tetrahedron(25.);
	tetrahedron.transform().set_global_translation(Point3(0, 0., 0.));
	ow.write(tetrahedron.mesh());

	BodyFactory::Box box(40., 50., 60.);
	box.transform().set_global_translation(Point3(100., 0., 0.));
	ow.write(box.mesh());

	BodyFactory::Cylinder cylinder(60., 30.);
	cylinder.transform().set_global_translation(Point3(200., 0., 0.));
	ow.write(cylinder.mesh());

	BodyFactory::Octahedron octahedron(40.);
	octahedron.transform().set_global_translation(Point3(0., 100., 0.));
	ow.write(octahedron.mesh());

	BodyFactory::Dodecahedron dodecahedron(20.);
	dodecahedron.transform().set_global_translation(Point3(100., 100., 0.));
	ow.write(dodecahedron.mesh());

	BodyFactory::Icosahedron icosahedron(30.);
	icosahedron.transform().set_global_translation(Point3(200, 100, 0.));
	ow.write(icosahedron.mesh());

	BodyFactory::SphereUV sphereUV(30.);
	sphereUV.transform().set_global_translation(Point3(0., 200., 0));
	ow.write(sphereUV.mesh());

	BodyFactory::SphereGeodesic sphereGeo(30.);
	sphereGeo.transform().set_global_translation(Point3(100., 200., 0));
	ow.write(sphereGeo.mesh());

	BodyFactory::Torus torus(25.,10.);
	torus.transform().set_global_translation(Point3(200., 200., 0.));
	ow.write(torus.mesh());

	ow.close();
	return 0;
}
///////////////////////////////////////////////////////////////////////////