#include "NurbsUtil.h"

#include <cassert>
#include <algorithm>
using namespace std;

#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "Mesh.h"

#include <cmath>
using namespace std;

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
void NurbsUtil::to_pointsmesh(const NurbsSurface& n,Mesh& m) //show the ctrl points lattice
{
	const vector<Point3>& points = n.points();
	int iNbPointsU = n.nb_points_u();
	int iNbPointsV = n.nb_points_v();

	m.clear();
	for(int u=0;u< iNbPointsU-1;u++)
		for (int v = 0; v < iNbPointsV-1; v++)
		{
			Point3 p1, p2, p3, p4;

			p1 = points[v * iNbPointsU + u];
			p2 = points[v * iNbPointsU + (u+1)];
			p3 = points[(v+1) * iNbPointsU + (u+1)];
			p4 = points[(v+1) * iNbPointsU + u];

			m.add_quad(p1, p2, p3, p4);
		}
}
///////////////////////////////////////////////////////////////////////////
