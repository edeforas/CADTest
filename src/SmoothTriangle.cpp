#include "SmoothTriangle.h"

///////////////////////////////////////////////////////////////////////////
SmoothTriangle::SmoothTriangle()
{
}

SmoothTriangle::~SmoothTriangle()
{
}

///////////////////////////////////////////////////////////////////////////
void SmoothTriangle::set_points(const Point3& P1, const Point3& P2, const Point3& P3) //also create middle control points
{
	_P1 = P1;
	_P2 = P2;
	_P3 = P3;

	_controlP1P2 = (P1 + P2 )* 0.5;
	_controlP1P3 = (P1 + P3) * 0.5;
	_controlP2P3 = (P2 + P3) * 0.5;
}

void SmoothTriangle::set_control_points(const Point3& controlP1P2, const Point3& controlP1P3, const Point3& controlP2P3)
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
		_controlP1P2 * 2. * s * u +
		_controlP1P3 * 2. * s * v +
		_controlP2P3 * 2. * u * v;

	return p;
}

void SmoothTriangle::add_to_mesh(Mesh& m, int iNbSegments) const
{
	int iNbVertices = m.nb_vertices();
	// create vertices
	for (int is = 0; is <= iNbSegments; is++)
	{
		double s = is / (double)iNbSegments;
		for (int iu = 0; iu <= iNbSegments - is; iu++)
		{
			// compute vertices

			double u = iu / (double)iNbSegments;

			Point3 p = eval(s, u);
			m.add_vertex(p);
		}
	}

	//link vertices to triangles
	int pos = iNbVertices;
	for (int is = 0; is <= iNbSegments - 1; is++)
	{
		int lineSize = iNbSegments - is+1;

		// add 1st triangle
		m.add_triangle(pos, pos + 1, pos + lineSize);
		pos += lineSize;
		
		for (int iu = 1; iu <= lineSize-4 ; iu++)
		{
			m.add_triangle(pos + iu , pos + iu + lineSize , pos + iu + lineSize-1);
			m.add_triangle(pos + iu, pos + iu + 1, pos + iu + lineSize );
		}
	} 
}