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
	void to_mesh(const NurbsSurface& n, Mesh& m, int iNbSegments=3);
	void to_pointsmesh(const NurbsSurface& n, Mesh& m);
	bool elevate_degree(NurbsCurve& n);
}
///////////////////////////////////////////////////////////////////////////

#endif