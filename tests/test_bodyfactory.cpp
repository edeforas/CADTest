#include "BodyFactory.h"
#include "Mesh.h"
#include "STLFile.h"

///////////////////////////////////////////////////////////////////////////
int main()
{
	// build and save objects
	Mesh m;
	
	BodyFactory::Tetrahedron tetrahedron(25.);
	m.add_mesh(tetrahedron.mesh());

	BodyFactory::Box box(40., 50., 60.);
	box.transform().set_global_translation(Point3(100., 0., 0.));
	m.add_mesh(box.mesh());

	BodyFactory::Cylinder cylinder(60., 50.);
	cylinder.transform().set_global_translation(Point3(200., 0., 0.));
	m.add_mesh(cylinder.mesh());

	BodyFactory::Octahedron octahedron(40.);
	octahedron.transform().set_global_translation(Point3(0., 100., 0.));
	m.add_mesh(octahedron.mesh());

	BodyFactory::Dodecahedron dodecahedron(20.);
	dodecahedron.transform().set_global_translation(Point3(100., 100., 0.));
	m.add_mesh(dodecahedron.mesh());

	BodyFactory::Icosahedron icosahedron(30.);
	icosahedron.transform().set_global_translation(Point3(200, 100, 0.));
	m.add_mesh(icosahedron.mesh());
	
	BodyFactory::SphereGeodesic sphere(30.);
	sphere.transform().set_global_translation(Point3(100., 200., 0));
	m.add_mesh(sphere.mesh());
	
	BodyFactory::SphereUV sphereUV(30.);
	//sphereUV.set_precision(16);
	sphereUV.transform().set_global_translation(Point3(0., 200., 0));
	m.add_mesh(sphereUV.mesh());
	
	BodyFactory::Torus torus(25.,10.);
	torus.transform().set_global_translation(Point3(200., 200., 0.));
	m.add_mesh(torus.mesh());
	
	STLFile::save("body_factory.stl", m);
	return 0;
}
///////////////////////////////////////////////////////////////////////////