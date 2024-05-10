#include "FaceBezierTriangles.h"

///////////////////////////////////////////////////////////////////////////
FaceBezierTriangles::FaceBezierTriangles()
{ }

FaceBezierTriangles::FaceBezierTriangles(const FaceBezierTriangles & f)
{
}

FaceBezierTriangles::~FaceBezierTriangles()
{ }

void FaceBezierTriangles::clear()
{
	//todo

}

void FaceBezierTriangles::add_to_mesh(Mesh& m, int iNbSegments)
{

	//todo

}
///////////////////////////////////////////////////////////////////////////
FaceBezierTriangles* FaceBezierTriangles::clone() const
{
	return new FaceBezierTriangles(*this);
}
///////////////////////////////////////////////////////////////////////////