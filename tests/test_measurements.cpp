#include "MeshFactory.h"

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
	Mesh m;
	MeshFactory::create_sphere_uv(1.,4,m);
	test_near(MeshMeasurements::is_closed(m), 0); //TODO

	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (i %2 ==0)
			m.unlink_triangle(i);
	}

	test_near(MeshMeasurements::is_closed(m), 0.);
}

void test_box_volume_surface()
{
	double radius = 1.;
	Mesh m;
	MeshFactory::create_box(2.,3.,4.,m);

	double dMeasuredVolume = MeshMeasurements::volume(m);
	double dTheoricalVolume = 2.*3.*4.;
	test_near(dMeasuredVolume, dTheoricalVolume);

	double dMeasuredSurface = MeshMeasurements::surface(m);
	double dTheoricalSurface = 2.*(2.*3.+3.*4.+2.*4.);
	test_near(dMeasuredSurface, dTheoricalSurface);
}

void test_sphere_uv_volume_surface()
{
	double radius = 1.;
	Mesh m;
	MeshFactory::create_sphere_uv(1.,100,m);

	double dMeasuredVolume = MeshMeasurements::volume(m);
	double dTheoricalVolume = 4. / 3. * 3.141592653 * (radius * radius * radius);
	test_near(dMeasuredVolume, dTheoricalVolume, 5.e-4);

	double dMeasuredSurface = MeshMeasurements::surface(m);
	double dTheoricalSurface = 4. * 3.141592653 * (radius * radius);
	test_near(dMeasuredSurface, dTheoricalSurface, 1.e-3);
}

void test_sphere_geodesic_volume_surface()
{
	double radius = 1.;
	Mesh m;
	MeshFactory::create_sphere_geodesic(1.,20,m);

	double dMeasuredVolume = MeshMeasurements::volume(m);
	double dTheoricalVolume = 4. / 3. * 3.141592653 * (radius * radius * radius);
	test_near(dMeasuredVolume, dTheoricalVolume,1.e-2);

	double dMeasuredSurface = MeshMeasurements::surface(m);
	double dTheoricalSurface = 4. * 3.141592653 * (radius * radius);
	test_near(dMeasuredSurface, dTheoricalSurface,1.e-2);
}

void test_torus_volume_surface()
{
	Mesh m;
	double radius = 1.;
	MeshFactory::create_torus(3,1.,100,m);

	double dMeasuredVolume = MeshMeasurements::volume(m);
	double dTheoricalVolume = 2. * 3.141592653 * 3.141592653 *3.*1.*1.; //2*pi*pi*R*r*r
	test_near(dMeasuredVolume, dTheoricalVolume, 2.e-2);

	double dMeasuredSurface = MeshMeasurements::surface(m);
	double dTheoricalSurface = 4. * 3.141592653 * 3.141592653 *3.*1.; //4*pi*pi*R*r
	test_near(dMeasuredSurface, dTheoricalSurface, 1.e-2);
}

///////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Test Start." << endl;

	test_mesh_closed();
	test_box_volume_surface();
	test_sphere_uv_volume_surface();
	test_sphere_geodesic_volume_surface();
	test_torus_volume_surface();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////