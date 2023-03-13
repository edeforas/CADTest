#ifndef NurbsUtil_
#define NurbsUtil_

#include <vector>
using namespace std;

class NurbsCurve; 
class NurbsSurface;
class NurbsSolid;
class Mesh;

///////////////////////////////////////////////////////////////////////////
namespace NurbsUtil
{
	void create_from_z(const vector<double>& z, int iSizeX, int iSizeY, int iDegree, NurbsSurface& n);
	void create_from_mesh(const Mesh & m, NurbsSolid& n);
	void to_mesh(const NurbsSurface& n, Mesh& m, int iNbSegments=5, bool bClearMesh=true);
	void to_mesh(const NurbsSolid& ns, Mesh& m, int iNbSegments=5);
	void to_controlpoints_mesh(const NurbsSurface& n, Mesh& m);
}
///////////////////////////////////////////////////////////////////////////

#endif