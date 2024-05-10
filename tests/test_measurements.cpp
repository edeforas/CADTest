#include "BodyFactory.h"

#include "Mesh.h"
#include "MeshMeasurements.h"

#include <iostream>
#include <cstdlib>
using namespace std;

void test_near(double a, double ref, double epsilon = 1.e-10, const string& sMessage = "")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}

void test_mesh_closed()
{
	BodyFactory::SphereUV sphere(1.);
	Mesh m = sphere.mesh();
	test_near(MeshMeasurements::is_closed(m), 0); //TODO

	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (rand() / (float)RAND_MAX > 0.5)
			m.unlink_triangle(i);
	}

	test_near(MeshMeasurements::is_closed(m), 0.);
}

void test_cube_volume_surface()
{
	double radius = 1.;
	BodyFactory::Box cube(1.,1.,1.);
	cube.set_mesh_precision(100);

	double dMeasuredVolume = MeshMeasurements::volume(cube.mesh());
	double dTheoricalVolume = 1.*1.*1.;
	test_near(dMeasuredVolume, dTheoricalVolume);

	double dMeasuredSurface = MeshMeasurements::surface(cube.mesh());
	double dTheoricalSurface = 6.*1.*1.;
	test_near(dMeasuredSurface, dTheoricalSurface);
}

void test_sphereuv_volume_surface()
{
	double radius = 1.;
	BodyFactory::SphereUV sphere(1.);
	sphere.set_mesh_precision(100);

	double dMeasuredVolume = MeshMeasurements::volume(sphere.mesh());
	double dTheoricalVolume = 4. / 3. * 3.141592653 * (radius * radius * radius);
	test_near(dMeasuredVolume, dTheoricalVolume, 5.e-4);

	double dMeasuredSurface = MeshMeasurements::surface(sphere.mesh());
	double dTheoricalSurface = 4. * 3.141592653 * (radius * radius);
	test_near(dMeasuredSurface, dTheoricalSurface, 1.e-3);
}

void test_spheregeodesic_volume_surface()
{
	double radius = 1.;
	BodyFactory::SphereGeodesic sphere(1.);
	sphere.set_mesh_precision(100);

	double dMeasuredVolume = MeshMeasurements::volume(sphere.mesh());
	double dTheoricalVolume = 4. / 3. * 3.141592653 * (radius * radius * radius);
	test_near(dMeasuredVolume, dTheoricalVolume,5.e-4);

	double dMeasuredSurface = MeshMeasurements::surface(sphere.mesh());
	double dTheoricalSurface = 4. * 3.141592653 * (radius * radius);
	test_near(dMeasuredSurface, dTheoricalSurface,5.e-4);
}

void test_torus_volume_surface()
{
	double radius = 1.;
	BodyFactory::Torus torus(3,1.);
	torus.set_mesh_precision(100);

	double dMeasuredVolume = MeshMeasurements::volume(torus.mesh());
	double dTheoricalVolume = 2. * 3.141592653 * 3.141592653 *3.*1.*1.; //2*pi*pi*R*r*r
	test_near(dMeasuredVolume, dTheoricalVolume, 2.e-2);

	double dMeasuredSurface = MeshMeasurements::surface(torus.mesh());
	double dTheoricalSurface = 4. * 3.141592653 * 3.141592653 *3.*1.; //4*pi*pi*R*r
	test_near(dMeasuredSurface, dTheoricalSurface, 1.e-2);
}

///////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Test Start." << endl;

	test_mesh_closed();
	test_cube_volume_surface();
	test_sphereuv_volume_surface();
	test_spheregeodesic_volume_surface();
	test_torus_volume_surface();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////