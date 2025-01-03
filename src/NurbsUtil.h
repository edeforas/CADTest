#ifndef NurbsUtil_
#define NurbsUtil_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;
class NurbsSolid;
class Mesh;

#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////
namespace NurbsUtil
{
	void to_mesh(const NurbsSurface& n, Mesh& m, int iNbSegments=5, bool bClearMesh=true);
	void to_mesh(const NurbsSolid& ns, Mesh& m, int iNbSegments=5);
	void to_pointsmesh(const NurbsSurface& n, Mesh& m);
}
///////////////////////////////////////////////////////////////////////////

#endif