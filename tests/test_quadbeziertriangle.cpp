#include "QuadBezierTriangle.h"
#include "Mesh.h"
#include "OBJFile.h"
#include "SmoothMesh.h"
#include "SmoothMeshFactory.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
using namespace std;

void test(bool b, string s = "")
{
	if (b == false)
	{
		cout << "condition: [" << s << "] is not realized!" << endl;
		exit(-1);
	}
}

void test_near(double a, double ref, double epsilon = 1.e-10, const string& sMessage = "")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}
///////////////////////////////////////////////////////////////////////////
void test_smoothmesh_shell()
{
	// octants of a sphere

	SmoothMesh sm;
	Mesh m;

	{
		QuadBezierTriangle st;
		st.set_points(Point3(1, 0, 0), Point3(0, 1, 0), Point3(0, 0, 1));
		st.set_control_points(Point3(1, 1, 0), Point3(1, 0, 1), Point3(0, 1, 1));
		sm.add_triangle(st);
	}

	{
		QuadBezierTriangle st;
		st.set_points(Point3(-1, 0, 0), Point3(0, 1, 0), Point3(0, 0, 1));
		st.set_control_points(Point3(-1, 1, 0), Point3(-1, 0, 1), Point3(0, 1, 1));
		sm.add_triangle(st);
	}

	{
		QuadBezierTriangle st;
		st.set_points(Point3(1, 0, 0), Point3(0, -1, 0), Point3(0, 0, 1));
		st.set_control_points(Point3(1, -1, 0), Point3(1, 0, 1), Point3(0, -1, 1));
		sm.add_triangle(st);
	}

	{
		QuadBezierTriangle st;
		st.set_points(Point3(1, 0, 0), Point3(0, 1, 0), Point3(0, 0, -1));
		st.set_control_points(Point3(1, 1, 0), Point3(1, 0, -1), Point3(0, 1, -1));
		sm.add_triangle(st);
	}

	sm.add_to_mesh(m, 11);
	OBJFile::save("test_smoothmesh_shell.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_sphere_octant()
{
	// octants of a sphere, test rational mode

	SmoothMesh sm;
	Mesh m;

	QuadBezierTriangle st;
	st.set_points(Point3(1, 0, 0), Point3(0, 1, 0), Point3(0, 0, 1));
	st.set_control_points(Point3(1, 1, 0), Point3(1, 0, 1), Point3(0, 1, 1));
	double winvsqrt2 = 1. / sqrt(2.);
	st.set_weights(1., 1., 1., winvsqrt2, winvsqrt2, winvsqrt2);
	sm.add_triangle(st);

	for (double s = 0.; s < 1.; s += 0.1)
		for (double t = 0.; t < 1.; t += 0.1)
		{
			Point3 p = st.eval(s, t);
			double n = p.norm();
			cout << s << " " << t << " " << n << endl;
			//test_near(n, 1., 1.e-10, "Norm should be 1.");
		}
	sm.add_to_mesh(m, 21);
	OBJFile::save("test_sphere_octant.obj", m);
}

///////////////////////////////////////////////////////////////////////////
void test_quarter_circle_deg2()
{
	/*
	cout << endl << "test_quarter_circle_deg2" << endl;

		NurbsCurve n;
		int degree = 2;
		vector<double> knots = { 0,0,0,1,1,1 };
		vector<double> weights = { 1.,1./sqrt(2.),1. };
		vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.) };

		n.set_degree(degree);
		n.set_knots(knots);
		n.set_weights(weights);
		n.set_points(points);

		for (double u = 0.; u <= 1.; u += 0.01)
		{
			Point3 p;
			n.evaluate(u, p);
			double norm = p.norm();
			//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
			test_near(norm, 1., 1.e-10);
		}
	*/
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_smoothmesh_shell();
	test_quarter_circle_deg2();
	test_sphere_octant();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////