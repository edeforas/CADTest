#include "CubicBezierTriangles.h"

///////////////////////////////////////////////////////////////////////////
CubicBezierTriangles::CubicBezierTriangles()
{
}

CubicBezierTriangles::~CubicBezierTriangles()
{
}

///////////////////////////////////////////////////////////////////////////
void CubicBezierTriangles::set_points(const Point3& P1, const Point3& P2, const Point3& P3)
{
	_P1 = P1;
	_P2 = P2;
	_P3 = P3;
}

void CubicBezierTriangles::set_control_points(const Point3& controlP1P2, const Point3& controlP2P1, const Point3& controlP1P3, const Point3& controlP3P1, const Point3& controlP2P3, const Point3& controlP3P2)
{
	_controlP1P2 = controlP1P2;
	_controlP2P1 = controlP2P1;

	_controlP1P3 = controlP1P3;
	_controlP3P1 = controlP3P1;

	_controlP2P3 = controlP2P3;
	_controlP3P2 = controlP3P2;
}

void CubicBezierTriangles::set_control_center(const Point3& controlCenter)
{
	_controlCenter = controlCenter;
}

void CubicBezierTriangles::set_normals(const Point3& normalP1, const Point3& normalP2, const Point3& normalP3)
{
	// compute control points from normals
	// from  https://en.wikipedia.org/wiki/Point-normal_triangle

	double wP1P2 = (_P2 - _P1).dot_product(normalP1);
	_controlP1P2 = (_P1 + _P1 + _P2 - normalP1 * wP1P2) / 3.;

	double wP2P1 = (_P1 - _P2).dot_product(normalP2);
	_controlP2P1 = (_P2 + _P2 + _P1 - normalP2 * wP2P1) / 3.;

	double wP1P3 = (_P3 - _P1).dot_product(normalP1);
	_controlP1P3 = (_P1 + _P1 + _P3 - normalP1 * wP1P3) / 3.;

	double wP3P1 = (_P1 - _P3).dot_product(normalP3);
	_controlP3P1 = (_P3 + _P3 + _P1 - normalP3 * wP3P1) / 3.;

	double wP2P3 = (_P3 - _P2).dot_product(normalP2);
	_controlP2P3 = (_P2 + _P2 + _P3 - normalP2 * wP2P3) / 3.;

	double wP3P2 = (_P2 - _P3).dot_product(normalP3);
	_controlP3P2 = (_P3 + _P3 + _P2 - normalP3 * wP3P2) / 3.;

	// compute central control point
	Point3 E = (_controlP1P2 + _controlP2P1 + _controlP1P3 + _controlP3P1 + _controlP2P3 + _controlP3P2) / 6.;
	Point3 V = (_P1 + _P2 + _P3) / 3.;
	_controlCenter = E + (E - V) / 2.;
}

