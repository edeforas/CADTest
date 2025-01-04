#include "NurbsUtil.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsSolid.h"
#include "Mesh.h"

#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std;

///////////////////////////////////////////////////////////////////////////
void NurbsUtil::to_pointsmesh(const NurbsSurface& n, Mesh& m) //show the ctrl points mesh lattice
{
	const vector<Point3>& points = n.points();
	int iNbPointsU = n.nb_points_u();
	int iNbPointsV = n.nb_points_v();

	m.clear();
	for (int u = 0; u < iNbPointsU - 1; u++)
		for (int v = 0; v < iNbPointsV - 1; v++)
		{
			Point3 p1, p2, p3, p4;

			p1 = points[v * iNbPointsU + u];
			p2 = points[v * iNbPointsU + (u + 1)];
			p3 = points[(v + 1) * iNbPointsU + (u + 1)];
			p4 = points[(v + 1) * iNbPointsU + u];

			m.add_quad(p1, p2, p3, p4);
		}
}
///////////////////////////////////////////////////////////////////////////
void NurbsUtil::to_mesh(const NurbsSurface& n, Mesh& m, int iNbSegments, bool bClearMesh)
{
	if (bClearMesh)
		m.clear();

	bool bIsClosedU = n.is_closed_u();
	bool bIsClosedV = n.is_closed_v();

	int iNbPointsStart = m.nb_vertices();
	int iNbPointsU = iNbSegments * n.nb_points_u();
	int iNbPointsV = iNbSegments * n.nb_points_v();

	if (iNbPointsU * iNbPointsU == 0)
		return;

	// add vertices, for now we keep all vertices, even if not used because closed
	Point3 p;
	for (int v = 0; v <= iNbPointsV; v++)
		for (int u = 0; u <= iNbPointsU; u++)
		{
			double du1 = (double)u / iNbPointsU;
			double dv1 = (double)v / iNbPointsV;

			n.evaluate(du1, dv1, p);
			m.add_vertex(p);
		}

	// add quad linked to vertices
	for (int v = 0; v < iNbPointsV; v++)
		for (int u = 0; u < iNbPointsU; u++)
		{
			int iEndU = u + 1;
			int iEndV = v + 1;

			if (bIsClosedU && (u == iNbPointsU - 1))
				iEndU = 0;

			if (bIsClosedV && (v == iNbPointsV - 1))
				iEndV = 0;

			m.add_quad(
				iNbPointsStart + u + (iNbPointsU + 1) * v,
				iNbPointsStart + iEndU + (iNbPointsU + 1) * v,
				iNbPointsStart + iEndU + (iNbPointsU + 1) * iEndV,
				iNbPointsStart + u + (iNbPointsU + 1) * iEndV
			);
		}
}
///////////////////////////////////////////////////////////////////////////
void NurbsUtil::to_mesh(const NurbsSolid& ns, Mesh& m, int iNbSegments)
{
	m.clear();
	for (const auto& f : ns.surfaces())
	{
		to_mesh(f, m, iNbSegments, false);
	}
}
///////////////////////////////////////////////////////////////////////////