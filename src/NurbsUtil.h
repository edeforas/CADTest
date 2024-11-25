#ifndef NurbsUtil_
#define NurbsUtil_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;
class Mesh;

#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////
namespace NurbsUtil
{
	void create_curve_from_points(const vector<Point3>& points, int degree, NurbsCurve& nc); //no rational, uniform
	void to_mesh(const NurbsSurface& n, Mesh& m, int iNbSegments=3);
	void create_circle(double dRadius, NurbsCurve& nc);
	void to_pointsmesh(const NurbsSurface& n, Mesh& m);
	bool elevate_degree(NurbsCurve& n);
}
///////////////////////////////////////////////////////////////////////////

#endif