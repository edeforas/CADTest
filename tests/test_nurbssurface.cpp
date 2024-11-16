#include "NurbsSurface.h"
#include "NurbsUtil.h"
#include "OBJFile.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
using namespace std;

void test_bool(bool b, const string& sMessage = "")
{
	if (!b)
	{
		cerr << "Test Error: " << sMessage.c_str() << endl;
		exit(-1);
	}
}

void test_near(double a, double ref, double epsilon=1.e-10,const string& sMessage="")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}

void test_square_surface()
{
	cout << endl << "test_square_surface" << endl;

	NurbsSurface n;
	int degree = 1;
	vector<Point3> points = { Point3(0.,0.,0.),Point3(1.,0.,0.),Point3(0.,1.,0.),Point3(1.,1.,0.) };

	n.set_degree(degree, degree);
	n.set_points(points,2,2);
	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	for (double u = 0.; u <= 1.; u += 0.1)
		for (double v = 0.; v <= 1.; v += 0.1)
		{
			Point3 p;
			n.evaluate(u, v, p);
			test_near(p.x(), u, 1e-10);
			test_near(p.y(), v, 1e-10);
			test_near(p.z(), 0., 1e-10);

			//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << endl;
	}

	Mesh m;
	n.to_mesh(m);
	OBJFile::save("test_square_surface.obj", m);
}

void test_ruled_surface_deg1()
{
	cout << endl << "Test ruled surface deg1" << endl;

	NurbsSurface n;
	int degree = 1;
	vector<Point3> points = { Point3(0.,0.,1.),Point3(1.,0.,-1.),Point3(0.,1.,-1.),Point3(1.,1.,1.) };

	n.set_degree(degree, degree);
	n.set_points(points,2,2);
	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	for (double u = 0.; u <= 1.; u += 0.1)
		for (double v = 0.; v <= 1.; v += 0.1)
		{
			Point3 p;
			n.evaluate(u, v, p);
			test_near(p.x(), u, 1e-10);
			test_near(p.y(), v, 1e-10);

			test_bool(p.z() <= 1.);
			test_bool(p.z() >= -1.);

			//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << endl;
		}

	Mesh m;
	n.to_mesh(m);
	OBJFile::save("test_ruled_surface_deg1.obj", m);
}

void test_ruled_surface_deg2()
{
	cout << endl << "Test ruled surface deg2" << endl;

	NurbsSurface n;
	int degreeU = 2;
	vector<Point3> points = { 
		Point3(0.,0.,0.),Point3(1.,1.,0.),Point3(2.,0.,0.),
		Point3(0.,1.,-1.),Point3(1.,0.,-1.),Point3(2.,1.,-1.)
	};

	n.set_degree(degreeU, 1);
	n.set_points(points,3,2);
	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	Mesh m;
	n.to_mesh(m);
	OBJFile::save("test_ruled_surface_deg2.obj", m);
}

void test_surface_deg1()
{
	cout << endl << "Test surface deg1" << endl;

	int nbPointsU = 7;
	int nbPointsV = 7;

	NurbsSurface n;
	int degree = 1;
	vector<Point3> points;
	
	for (int v = 0; v < nbPointsV; v++)
		for(int u= 0; u < nbPointsU; u++)
			points.push_back(Point3(u,v,(float)rand()/RAND_MAX));

	n.set_degree(degree, degree);
	n.set_points(points, nbPointsU, nbPointsV);

	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	Mesh m;
	n.to_mesh(m,20);
	OBJFile::save("test_surface_deg1.obj", m);
}

void test_surface_deg2()
{
	cout << endl << "Test surface deg2" << endl;

	int nbPointsU = 7;
	int nbPointsV = 7;

	NurbsSurface n;
	int degree = 2;
	vector<Point3> points;

	for (int v = 0; v < nbPointsV; v++)
		for (int u = 0; u < nbPointsU; u++)
			points.push_back(Point3(u, v, (float)rand() / RAND_MAX));

	n.set_degree(degree, degree);
	n.set_points(points, nbPointsU, nbPointsV);

	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	Mesh m;
	n.to_mesh(m,20);
	OBJFile::save("test_surface_deg2.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsurface_cylinder()
{
	cout << endl << "Test cylinder using nurbscurve and extrude" << endl;

	//create profile and extrude
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

	// extrude
	int degreeV = 1;
	vector<double> knotsV = { 0., 0., 1., 1. };

	NurbsSurface n;
	n.set_degree(degreeU, degreeV);
	n.set_knots_u(knotsU);
	n.set_knots_v(knotsV);
	n.set_weights(weights);
	n.set_points(points,9,2);

	Mesh m;
	n.to_mesh(m);

	OBJWriter ow;
	ow.open("test_nurbsurface_cylinder.obj");
	ow.write(m);

	// add points quad meshes
	NurbsUtil::to_pointsmesh(n, m);
	m.set_color(0xff);
	ow.write(m);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_square_surface();
	test_ruled_surface_deg1();
	test_ruled_surface_deg2();
	test_surface_deg1();
	test_surface_deg2();
	test_nurbsurface_cylinder();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////