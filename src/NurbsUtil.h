#ifndef NurbsUtil_
#define NurbsUtil_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;
class Mesh;

///////////////////////////////////////////////////////////////////////////
namespace NurbsUtil
{
	void create_circle(double dRadius, NurbsCurve& nc);
	void to_pointsmesh(const NurbsSurface& n, Mesh& m);
}
///////////////////////////////////////////////////////////////////////////

#endif