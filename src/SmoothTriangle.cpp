#include "SmoothTriangle.h"

///////////////////////////////////////////////////////////////////////////
SmoothTriangle::SmoothTriangle()
{ }

SmoothTriangle::~SmoothTriangle()
{ }

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

Point3 SmoothTriangle::eval(double s, double, u, double v = -1.) const
{
	if (v == -1.)
		v = 1. - s - u;

	Point3 p = s * s * _P1 + u * u * _P2 + v * v * _P3 + 3. * (_controlP1P2 * s * u + _controlP1P3 * s * v + _controlP2P3 * u * v);
	return p;
}

void SmoothTriangle::to_mesh(Mesh& m, int iNbSegments) const
{
	m.clear();

	//todo
}
