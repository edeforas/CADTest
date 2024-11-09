#include "NurbsUtil.h"

#include <cassert>
#include <algorithm>
using namespace std;

#include "NurbsCurve.h"
#include "NurbsSurface.h"

///////////////////////////////////////////////////////////////////////////
void NurbsUtil::create_circle(double dRadius, NurbsCurve& nc)
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