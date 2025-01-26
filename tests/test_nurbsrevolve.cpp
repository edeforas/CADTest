#include "NurbsRevolve.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsFactory.h"
#include "NurbsUtil.h"

#include "MeshUtil.h"
#include "OBJFile.h"

#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

void test_near(double a, double ref, double epsilon=1.e-10,const string& sMessage="")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsrevolve_flatdisk()
{
	cout << endl << "test_nurbsrevolve_flatdisk using 4 quarter circles as borders" << endl;

	// create circle profile using 4 quarter circles as borders
	// use revolve surface instead, to create a disk
	int degreeU = 2;
	vector<double> knots = { 0., 0., 0., 1., 1., 1. };
	vector<double> weights = { 1.,1. / sqrt(2.),1.,   1. / sqrt(2.),1.,1. / sqrt(2.),   1.,1. / sqrt(2.),1. };
	vector<Point3> points = {
		Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.),
		Point3(1.,-1,0.),Point3(0.,0.,0),Point3(-1.,1.,0.),
		Point3(0.,-1.,0.),Point3(-1.,-1.,0.),Point3(-1.,0.,0.),
	};

	NurbsSurface n;
	n.set_degree(2, 2);
	n.set_knots_u(knots);
	n.set_knots_v(knots);
	n.set_weights(weights);
	n.set_points(points, 3, 3);

	Mesh m;
	NurbsUtil::to_mesh(n, m, 10);
	OBJFile::save("test_nurbsrevolve_flatdisk.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsrevolve_cylinder()
{
	cout << endl << "test_nurbsrevolve_cylinder" << endl;

	//creation with elementary operators
	int degreeU = 2;
	vector<double> knotsU = { 0., 0., 0., 0.25, 0.25, 0.5, 0.5, 0.75, 0.75, 1., 1., 1. };
	vector<double> weights = {
		1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,
		1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.
	};

	vector<Point3> points = {
		Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.),
		Point3(-1.,1.,0.),Point3(-1.,0.,0.),Point3(-1.,-1.,0.),
		Point3(0.,-1.,0.),Point3(1.,-1.,0.),Point3(1.,0.,0.),
		Point3(1.,0.,2.),Point3(1.,1.,2.),Point3(0.,1.,2.),
		Point3(-1.,1.,2.),Point3(-1.,0.,2.),Point3(-1.,-1.,2.),
		Point3(0.,-1.,2.),Point3(1.,-1.,2.),Point3(1.,0.,2.),
	};

	int degreeV = 1;
	vector<double> knotsV = { 0., 0., 1., 1. };

	NurbsSurface n;
	n.set_degree(degreeU, degreeV);
	n.set_knots_u(knotsU);
	n.set_knots_v(knotsV);
	n.set_weights(weights);
	n.set_points(points, 9, 2);

	Mesh m;
	NurbsUtil::to_mesh(n, m);
	OBJFile::save("test_nurbsrevolve_cylinder.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsrevolve_vase()
{
	cout << endl << "test_nurbsrevolve_vase" << endl;

	//create profile curve
	vector<Point3> points = {
		Point3(0.,0.,0.),Point3(1.,0.,0.),
		Point3(1.,0.,0.),Point3(2.,1.,1.),Point3(1.,1.,2.),
		Point3(2.,2.,3.),Point3(3.,0.,4.),Point3(0.,2.,5.)
	};
	NurbsCurve nc;
	NurbsFactory::create_curve_from_points(points, 3, nc);

	// revolve
	NurbsRevolve nr;
	NurbsSurface ns;
	nr.revolve(nc, ns);

	Mesh m;
	NurbsUtil::to_mesh(ns,m,10);

	OBJWriter ow;
	ow.open("test_nurbsrevolve_vase.obj");
	ow.write(m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsrevolve_sphere()
{
	cout << endl << "test_nurbsrevolve_sphere" << endl;

	//creation with elementary operators
	//create profile curve: half circle
	NurbsCurve nc;
	vector<Point3> points = {
		Point3(0., 0.,-1.),Point3(0.,1.,-1.),Point3(0., 1.,0.),Point3(0.,1.,1.),Point3(0.,0.,1.)
	};
	vector<double> weights = { 1. , 1. / sqrt(2.),1., 1. / sqrt(2.), 1. };
	vector<double> knots = { 0., 0., 0., 0.5, 0.5, 1., 1., 1. };
	nc.set_degree(2);
	nc.set_points(points);
	nc.set_weights(weights);
	nc.set_knots(knots);

	NurbsRevolve nr;
	NurbsSurface ns;
	nr.revolve(nc, ns);

	Mesh m;
	NurbsUtil::to_mesh(ns, m, 10);

	// test all points are on distance 1. to center
	for (int i = 0; i < m.nb_vertices(); i++)
	{
		Point3 p;
		m.get_vertex(i, p);
		test_near(p.norm(), 1.);
	}

	OBJWriter ow;
	ow.open("test_nurbsrevolve_sphere.obj");
	ow.write(m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsrevolve_create_sphere()
{
	// use nurbs factory that call revolve
	cout << endl << "test_nurbsrevolve_create_sphere" << endl;

	NurbsSurface ns;
	NurbsFactory::create_sphere(1., ns);

	Mesh m;
	NurbsUtil::to_mesh(ns, m, 10);

	// test all points are on distance 1. to center
	for (int i = 0; i < m.nb_vertices(); i++)
	{
		Point3 p;
		m.get_vertex(i, p);
		test_near(p.norm(), 1.);
	}

	OBJWriter ow;
	ow.open("test_nurbsrevolve_create_sphere.obj");
	ow.write(m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsrevolve_create_torus()
{
	// call nurbs factory
	cout << endl << "test_nurbsrevolve_create_torus" << endl;

	NurbsSurface ns;
	NurbsFactory::create_torus(5., 2., ns);

	Mesh m;
	NurbsUtil::to_mesh(ns, m, 10);

	OBJWriter ow;
	ow.open("test_nurbsrevolve_create_torus.obj");
	ow.write(m);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_nurbsrevolve_cylinder();
	test_nurbsrevolve_flatdisk();

	test_nurbsrevolve_vase();
	test_nurbsrevolve_sphere();
	test_nurbsrevolve_create_sphere();
	test_nurbsrevolve_create_torus();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////