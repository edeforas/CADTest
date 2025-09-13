#include "SmoothTriangle.h"

///////////////////////////////////////////////////////////////////////////
SmoothTriangle::SmoothTriangle()
{
}

SmoothTriangle::~SmoothTriangle()
{
}

///////////////////////////////////////////////////////////////////////////
void SmoothTriangle::set_points(const Point3& P1, const Point3& P2, const Point3& P3)
{
	_P1 = P1;
	_P2 = P2;
	_P3 = P3;
}

void SmoothTriangle::set_control_P(const Point3& controlP1P2, const Point3& controlP1P3, const Point3& controlP2P3)
{
	_controlP1P2 = controlP1P2;
	_controlP1P3 = controlP1P3;
	_controlP2P3 = controlP2P3;
}

Point3 SmoothTriangle::eval(double s, double u, double v ) const
{
	// autocompute v by default
	if (v == -1.)
		v = 1. - s - u;

	Point3 p =
		_P1 * s * s +
		_P2 * u * u +
		_P3 * v * v +
		_controlP1P2 * 3. * s * u +
		_controlP1P3 * 3. * s * v +
		_controlP2P3 * 3. * u * v;

	return p;
}

void SmoothTriangle::to_mesh(Mesh& m, int iNbSegments) const
{
	m.clear();

	// add all the vertices
	for (int is=0; is < iNbSegments; is++)
		for (int iu = 0; iu < iNbSegments; iu++)
		{
			// compute vertices
			
			double s = is / (double)iNbSegments;
			double u = iu / (double)iNbSegments;

			Point3 p = eval(s, u);
			m.add_vertex(p);
		}

	//link all the vertices to triangles

}
