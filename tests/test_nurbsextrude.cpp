#include "NurbsExtrude.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
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

void test_extrude_cylinder()
{
	cout << endl << "Test extrude cylinder using nurbscurve and extrude" << endl;

	//circle profile definition
	int degree = 2;
	vector<double> knots = { 0., 0., 0., 0.25, 0.25, 0.5, 0.5, 0.75, 0.75, 1., 1., 1. };
	vector<double> weights = { 1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1. };
	vector<Point3> points = {
		Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.),
		Point3(-1.,1.,0.),Point3(-1.,0.,0.),Point3(-1.,-1.,0.),
		Point3(0.,-1.,0.),Point3(1.,-1.,0.),Point3(1.,0.,0.),
	};

	//create profile curve
	NurbsCurve nc;
	nc.set_degree(degree);
	nc.set_knots(knots);
	nc.set_weights(weights);
	nc.set_points(points);

	Point3 direction(0, 0, 2.);
	NurbsSurface ns;

	// extrude
	NurbsExtrude ne;
	ne.extrude(nc, direction, ns);

	Mesh m;
	ns.to_mesh(m);
	OBJFile::save("test_extrude_cylinder.obj", m);
}

///////////////////////////////////////////////////////////////////////////
int main()
{
	test_extrude_cylinder();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////