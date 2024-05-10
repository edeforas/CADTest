#include "FaceBezierPatches.h"

///////////////////////////////////////////////////////////////////////////
FaceBezierPatches::FaceBezierPatches()
{ }

FaceBezierPatches::FaceBezierPatches(const FaceBezierPatches & f):
	_vP(f._vP)
{ }

FaceBezierPatches::~FaceBezierPatches()
{ }

void FaceBezierPatches::clear()
{
	_vP.clear();
}

void FaceBezierPatches::add_to_mesh(Mesh& m, int iNbSegments)
{
	//todo

}
///////////////////////////////////////////////////////////////////////////
void FaceBezierPatches::set_points(const vector<Point3>& vP)
{
	_vP = vP;
}
///////////////////////////////////////////////////////////////////////////
FaceBezierPatches* FaceBezierPatches::clone() const
{
	return new FaceBezierPatches(*this);
}
///////////////////////////////////////////////////////////////////////////