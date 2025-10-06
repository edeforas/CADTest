#include "SmoothMeshFactory.h"
#include "SmoothMesh.h"
#include "Mesh.h"
#include "OBJFile.h"
#include "Transform.h"

///////////////////////////////////////////////////////////////////////////
int main()
{
	Mesh mesh;
	SmoothMesh sm;
	OBJWriter ow;
	ow.open("test_smoothmeshfactory.obj");

	SmoothMeshFactory::create_tetrahedron(25.,sm);
	sm.add_to_mesh(mesh,11);

	SmoothMeshFactory::create_box(40., 50., 60., sm);
	sm.apply_transform(Translation(Point3(100., 0., 0.)));
	sm.add_to_mesh(mesh, 11);

	SmoothMeshFactory::create_octahedron(40., sm);
	sm.apply_transform(Translation(Point3(0., 100., 0.)));
	sm.add_to_mesh(mesh, 11);

	SmoothMeshFactory::create_dodecahedron(20., sm);
	sm.apply_transform(Translation(Point3(100., 100., 0.)));
	sm.add_to_mesh(mesh, 11);
	
	SmoothMeshFactory::create_icosahedron(30., sm);
	sm.apply_transform(Translation(Point3(200, 100, 0.)));
	sm.add_to_mesh(mesh, 11);

	SmoothMeshFactory::create_sphere(30., sm);
	sm.apply_transform(Translation(Point3(0., 200., 0)));
	sm.add_to_mesh(mesh, 11);


	/*
	SmoothMeshFactory::create_cylinder(60., 30.,10, m);
	m.apply_transform(Translation(Point3(200., 0., 0.)));


	SmoothMeshFactory::create_sphere_geodesic(30.,10,m);
	m.apply_transform(Translation(Point3(100., 200., 0)));

	SmoothMeshFactory::create_torus(25.,15.,8,m);
	m.apply_transform(Translation(Point3(200., 200., 0.)));
	*/

	ow.write(mesh);
	ow.close();
	return 0;
}
///////////////////////////////////////////////////////////////////////////