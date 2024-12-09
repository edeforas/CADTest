#ifndef NurbsFactory_
#define NurbsFactory_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;
class NurbsSolid;

#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////
namespace NurbsFactory
{
	void create_curve_from_points(const vector<Point3>& points, int degree, NurbsCurve& nc); //no rational, uniform
	void create_circle(double dRadius, NurbsCurve& nc);
	void create_disk(double dRadius, NurbsSurface& ns);
	void create_sphere(double dRadius, NurbsSurface& ns);
	void create_cylinder(double dRadius,double dHeight, NurbsSolid& nsd);
	void create_torus(double dMajorRadius, double dMinorRadius, NurbsSurface& ns);
}
///////////////////////////////////////////////////////////////////////////

#endif