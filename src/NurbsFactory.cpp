#include "NurbsFactory.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsRevolve.h"

#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std;

///////////////////////////////////////////////////////////////////////////
void NurbsFactory::create_circle(double dRadius, NurbsCurve& nc)
{
	nc.clear();

	NurbsCurve n;
	int degree = 2;
	vector<double> knots = { 0., 0., 0., 0.25, 0.25, 0.5, 0.5, 0.75, 0.75, 1., 1., 1. };
	vector<double> weights = { 1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1. };
	vector<Point3> points = {
		Point3(1.,0.,0.) * dRadius,Point3(1.,1.,0.) * dRadius,Point3(0.,1.,0.) * dRadius,
		Point3(-1.,1.,0.) * dRadius,Point3(-1.,0.,0.) * dRadius,Point3(-1.,-1.,0.) * dRadius,
		Point3(0.,-1.,0.) * dRadius,Point3(1.,-1.,0.) * dRadius,Point3(1.,0.,0.) * dRadius
	};

	nc.set_degree(degree);
	nc.set_knots(knots);
	nc.set_weights(weights);
	nc.set_points(points);
}
///////////////////////////////////////////////////////////////////////////
void NurbsFactory::create_curve_from_points(const vector<Point3>& points, int degree,NurbsCurve& nc) //no rational, uniform
{
	nc.clear();
	nc.set_degree(degree);
	nc.set_points(points);

	nc.set_uniform();
	nc.set_equals_weights();
}
///////////////////////////////////////////////////////////////////////////
void NurbsFactory::create_sphere(double dRadius,NurbsSurface& ns)
{
	ns.clear();

	//create profile curve: half circle
	NurbsCurve nc;
	vector<Point3> points = {
		Point3(0., 0.,-1.)* dRadius,
		Point3(0.,1.,-1.)* dRadius,
		Point3(0., 1.,0.)* dRadius,
		Point3(0.,1.,1.)* dRadius,
		Point3(0.,0.,1.)* dRadius
	};

	vector<double> weights = { 1. , 1. / sqrt(2.),1., 1. / sqrt(2.), 1. };
	vector<double> knots = { 0., 0., 0., 0.5, 0.5, 1., 1., 1. };
	nc.set_degree(2);
	nc.set_points(points);
	nc.set_weights(weights);
	nc.set_knots(knots);

	// revolve
	NurbsRevolve nr;
	nr.revolve(nc, ns);
}
///////////////////////////////////////////////////////////////////////////
void NurbsFactory::create_cylinder(double dRadius, double dHeight, NurbsSurface& ns)
{
	ns.clear();

	//create profile curve
	NurbsCurve nc;
	vector<Point3> points = {
		Point3(0., 0.,-dHeight / 2.),
		Point3(0.,dRadius,-dHeight / 2.),
		Point3(0.,dRadius,dHeight / 2.),
		Point3(0., 0.,dHeight / 2.),
	};

	nc.set_degree(1);
	nc.set_points(points);
	nc.set_uniform();
	nc.set_equals_weights();

	// revolve
	NurbsRevolve nr;
	nr.revolve(nc, ns);
}
///////////////////////////////////////////////////////////////////////////
void NurbsFactory::create_torus(double dMajorRadius,double dMinorRadius, NurbsSurface& ns)
{
	ns.clear();

	//create profile curve: circle and transform it
	NurbsCurve nc;
	NurbsFactory::create_circle(dMinorRadius, nc);
	for (int i = 0; i < nc.nb_points(); i++)
	{
		Point3& p = nc.points()[i];

		p.x() += dMajorRadius;

		double dz = p.z();
		p.z() = p.y();
		p.y() = -dz;
	}

	// revolve
	NurbsRevolve nr;
	nr.revolve(nc, ns);
}
