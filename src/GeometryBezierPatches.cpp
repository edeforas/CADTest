#include "SurfaceBezierPatches.h"

///////////////////////////////////////////////////////////////////////////
SurfaceBezierPatches::SurfaceBezierPatches()
{ }

SurfaceBezierPatches::~SurfaceBezierPatches()
{ }

void SurfaceBezierPatches::clear()
{
	_vP.clear();
}

void SurfaceBezierPatches::add_to_mesh(Mesh& m, int iNbSegments)
{
	//todo

}
///////////////////////////////////////////////////////////////////////////
void SurfaceBezierPatches::set_points(const vector<Point3>& vP)
{
	_vP = vP;
}
