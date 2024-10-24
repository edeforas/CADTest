#include "NurbsSurface.h"

#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

void test_near(double a, double ref, double epsilon,const string& sMessage="")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}

void test_simple_surface()
{
	cout << endl << "Test simple square" << endl;

	NurbsSurface n;
	int degree = 1;
	vector<double> knots = { 0,0,1,1 };
	vector<double> weights = { 1.,1.,1.,1. };
	vector<Point3> points = { Point3(0.,0.,0.),Point3(1.,0.,0.),Point3(0.,1.,0.),Point3(1.,1.,0.) };

	n.set_degree(degree, degree);
	n.set_knots_u(knots);
	n.set_knots_v(knots);
	n.set_weights(weights);
	n.set_points(points);

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
}

///////////////////////////////////////////////////////////////////////////
int main()
{
	//test_simple_surface();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////