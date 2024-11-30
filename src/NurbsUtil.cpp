#include "NurbsUtil.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "Mesh.h"

#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std;

///////////////////////////////////////////////////////////////////////////
void NurbsUtil::to_pointsmesh(const NurbsSurface& n,Mesh& m) //show the ctrl points mesh lattice
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
void NurbsUtil::to_mesh(const NurbsSurface& n, Mesh& m, int iNbSegments)
{
	m.clear();

	int iNbSegmentsU = iNbSegments * n.nb_points_u();
	int iNbSegmentsV = iNbSegments * n.nb_points_v();

	if (iNbSegmentsU * iNbSegmentsU == 0)
		return;

	Point3 p;
	for (int v = 0; v < iNbSegmentsV; v++)
		for (int u = 0; u < iNbSegmentsU; u++)
		{
			//TODO slow
			double du1 = (double)u / iNbSegmentsU;
			double dv1 = (double)v / iNbSegmentsV;
			double du2 = (double)(u + 1) / iNbSegmentsU;
			double dv2 = (double)(v + 1) / iNbSegmentsV;

			Point3 p1, p2, p3, p4;
			n.evaluate(du1, dv1, p1);
			n.evaluate(du2, dv1, p2);
			n.evaluate(du2, dv2, p3);
			n.evaluate(du1, dv2, p4);

			m.add_quad(p1, p2, p3, p4);
		}
}
///////////////////////////////////////////////////////////////////////////
bool NurbsUtil::elevate_degree(NurbsCurve& n)
{
	//from paper DIRECT DEGREE ELEVATION OF NURBS CURVES Kestutis Jankauskas, Dalius Rubliauskas
	if (n.degree() == 1)
	{	
		//elevate knots


	}

	//todo
	return false;
}
///////////////////////////////////////////////////////////////////////////