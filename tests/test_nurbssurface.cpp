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

void test_nurbssurface_square()
{
	cout << endl << "test_nurbssurface_square" << endl;

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
	NurbsUtil::to_mesh(n, m);
	OBJFile::save("test_nurbssurface_square.obj", m);
}

void test_nurbssurface_ruled_deg1()
{
	cout << endl << "test_nurbssurface_ruled_deg1" << endl;

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
	NurbsUtil::to_mesh(n, m, 10);;
	OBJFile::save("test_nurbssurface_ruled_deg1.obj", m);
}

void test_nurbssurface_ruled_deg2()
{
	cout << endl << "test_nurbssurface_ruled_deg2" << endl;

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
	NurbsUtil::to_mesh(n, m, 10);
	OBJFile::save("test_nurbssurface_ruled_deg2.obj", m);
}

void test_nurbssurface_deg1()
{
	cout << endl << "test_nurbssurface_deg1" << endl;

	int nbPointsU = 11;
	int nbPointsV = 11;

	NurbsSurface n;
	int degree = 1;
	vector<Point3> points;
	
	for (int v = 0; v < nbPointsV; v++)
		for(int u= 0; u < nbPointsU; u++)
			points.push_back(Point3(u,v,(float)rand()/RAND_MAX*3.));

	n.set_degree(degree, degree);
	n.set_points(points, nbPointsU, nbPointsV);

	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	Mesh m;
	NurbsUtil::to_mesh(n, m, 20);
	OBJFile::save("test_nurbssurface_deg1.obj", m);
}

void test_nurbssurface_deg2()
{
	cout << endl << "test_nurbssurface_deg2" << endl;

	int nbPointsU = 11;
	int nbPointsV = 11;

	NurbsSurface n;
	int degree = 2;
	vector<Point3> points;

	for (int v = 0; v < nbPointsV; v++)
		for (int u = 0; u < nbPointsU; u++)
			points.push_back(Point3(u, v, (float)rand() / RAND_MAX*3.));

	n.set_degree(degree, degree);
	n.set_points(points, nbPointsU, nbPointsV);

	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	Mesh m;
	NurbsUtil::to_mesh(n, m, 20);
	OBJFile::save("test_nurbssurface_deg2.obj", m);
}

///////////////////////////////////////////////////////////////////////////
void test_nurbssurface_deg3()
{
	cout << endl << "test_nurbssurface_deg3" << endl;

	int nbPointsU = 11;
	int nbPointsV = 11;

	NurbsSurface n;
	int degree = 3;
	vector<Point3> points;

	for (int v = 0; v < nbPointsV; v++)
		for (int u = 0; u < nbPointsU; u++)
			points.push_back(Point3(u, v, (float)rand() / RAND_MAX*3.));

	n.set_degree(degree, degree);
	n.set_points(points, nbPointsU, nbPointsV);

	n.set_uniform_u();
	n.set_uniform_v();
	n.set_equals_weights();

	Mesh m;
	NurbsUtil::to_mesh(n, m, 20);
	OBJFile::save("test_nurbssurface_deg3.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbssurface_degxy()
{
	cout << endl << "test_nurbssurface_degxy" << endl;

	int nbPointsU = 7;
	int nbPointsV = 7;
	OBJWriter ow;
	ow.open("test_nurbssurface_degxy.obj");

	vector<Point3> points,pt;
	for (int v = 0; v < nbPointsV; v++)
		for (int u = 0; u < nbPointsU; u++)
			points.push_back(Point3(u, v, 2.*(float)rand() / RAND_MAX));

	for(int uDeg=1; uDeg<=3;uDeg++)
		for (int vDeg = 1; vDeg <= 3; vDeg++)
		{
			NurbsSurface n;

			n.set_degree(uDeg, vDeg);

			//translate point
			pt = points;
			for (auto& p : pt)
			{
				p.x() += uDeg * nbPointsU*1.1;
				p.y() += vDeg * nbPointsV*1.1;
			}

			n.set_points(pt, nbPointsU, nbPointsV);
			n.set_uniform_u();
			n.set_uniform_v();
			n.set_equals_weights();

			Mesh m;
			NurbsUtil::to_mesh(n, m, 10);
			m.set_color((uDeg * 50 + 100) * 256 * 256 + (vDeg * 50 + 100) * 256); //red is degu , green is degv
			ow.write(m);
		}
	ow.close();
}
///////////////////////////////////////////////////////////////////////////
void test_nurbssurface_cylinder()
{
	cout << endl << "test_nurbssurface_cylinder using nurbscurve and extrude" << endl;

	//create circle profile and extrude
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
	NurbsUtil::to_mesh(n, m);
	OBJFile::save("test_nurbssurface_cylinder.obj", m);
}

///////////////////////////////////////////////////////////////////////////
void test_nurbssurface_flatdisk()
{
	cout << endl << "test_nurbssurface_flatdisk using 4 quarter circles as borders" << endl;

	//create circle profile using 4 quarter circles as borders
	int degreeU = 2;

	vector<double> knots = { 0., 0., 0., 1., 1., 1. };
	vector<double> weights = { 1.,1. / sqrt(2.),1.,   1. / sqrt(2.),1.,1. / sqrt(2.),   1.,1. / sqrt(2.),1. };

	vector<Point3> points = {
		Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.),
		Point3(1.,-1,0.),Point3(0.,0.,0),Point3(-1.,1.,0.),
		Point3(0.,-1.,0.),Point3(-1.,-1.,0.),Point3(-1.,0.,0.),
	};

	// extrude

	NurbsSurface n;
	n.set_degree(2, 2);
	n.set_knots_u(knots);
	n.set_knots_v(knots);
	n.set_weights(weights);
	n.set_points(points, 3, 3);

	Mesh m;
	NurbsUtil::to_mesh(n, m, 10);
	OBJFile::save("test_nurbssurface_flatdisk.obj", m);
}

///////////////////////////////////////////////////////////////////////////
int main()
{
	test_nurbssurface_square();
	test_nurbssurface_ruled_deg1();
	test_nurbssurface_ruled_deg2();
	test_nurbssurface_deg1();
	test_nurbssurface_deg2();
	test_nurbssurface_deg3();
	test_nurbssurface_degxy();
	test_nurbssurface_cylinder();
	test_nurbssurface_flatdisk();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////