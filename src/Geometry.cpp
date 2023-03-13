#include "Geometry.h"

#include <cmath>

inline double squared(double a) //todo factorize ?
{
	return a * a;
}

///////////////////////////////////////////////////////////////////////////
Point3::Point3()
{
	_x = 0.; _y = 0.; _z = 0.;
}

Point3::Point3(double x, double y, double z)
{
	_x = x; _y = y; _z = z;
}


double& Point3::x()
{
	return _x;
}

double& Point3::y()
{
	return _y;
}

double& Point3::z()
{
	return _z;
}

const double& Point3::x() const
{
	return _x;
}

const double& Point3::y() const
{
	return _y;
}

const double& Point3::z() const
{
	return _z;
}


Point3& Point3::operator+=(const Point3& p)
{
	_x += p._x;
	_y += p._y;
	_z += p._z;

	return *this;
}

Point3& Point3::operator-=(const Point3& p)
{
	_x -= p._x;
	_y -= p._y;
	_z -= p._z;

	return *this;
}

Point3& Point3::operator*=(double d)
{
	_x *= d;
	_y *= d;
	_z *= d;

	return *this;
}

Point3& Point3::operator/=(double d)
{
	_x /= d;
	_y /= d;
	_z /= d;

	return *this;
}


Point3 Point3::operator+(const Point3& p) const
{
	Point3 res;

	res._x = _x + p._x;
	res._y = _y + p._y;
	res._z = _z + p._z;

	return res;
}

Point3 Point3::operator*(double d) const
{
	Point3 res;

	res._x = d * _x;
	res._y = d * _y;
	res._z = d * _z;

	return res;
}

Point3 Point3::operator/(double d) const
{
	Point3 res;

	res._x = _x / d;
	res._y = _y / d;
	res._z = _z / d;

	return res;
}

Point3 Point3::operator-(const Point3& p) const
{
	Point3 res;

	res._x = _x - p._x;
	res._y = _y - p._y;
	res._z = _z - p._z;

	return res;
}

double Point3::distance_square(const Point3& p) const
{
	return squared(_x - p._x) + squared(_y - p._y) + squared(_z - p._z);
}

double Point3::dot_product(const Point3& p) const
{
	return _x * p._x + _y * p._y + _z * p._z;
}

Point3 Point3::cross_product(const Point3& p) const
{
	// from https://en.wikipedia.org/wiki/Cross_product
	return Point3(_y * p._z - _z * p._y, _z * p._x - _x * p._z, _x * p._y - _y * p._x);
}

double Point3::norm() const
{
	return sqrt(_x * _x + _y * _y + _z * _z);
}

double Point3::norm_square() const
{
	return _x * _x + _y * _y + _z * _z;
}

Point3 Point3::normalized() const
{
	double d = 1. / norm();
	return this->operator*(d);
}
void Point3::normalize()
{
	double d = 1. / norm();
	this->operator*=(d);
}
///////////////////////////////////////////////////////////////////////////
Line3::Line3()
{
}

Line3::Line3(const Point3& p1, const Point3& p2) :
	_p1(p1),
	_p2(p2)
{
}

const Point3& Line3::p1() const
{
	return _p1;
}

const Point3& Line3::p2() const
{
	return _p2;
}

void Line3::set_p1(const Point3& p)
{
	_p1 = p;
}

void Line3::set_p2(const Point3& p)
{
	_p2 = p;
}
///////////////////////////////////////////////////////////////////////////
Segment3::Segment3()
{
}

Segment3::Segment3(const Point3& p1, const Point3& p2) :
	_p1(p1),
	_p2(p2)
{
}

const Point3& Segment3::p1() const
{
	return _p1;
}

const Point3& Segment3::p2() const
{
	return _p2;
}

void Segment3::set_p1(const Point3& p)
{
	_p1 = p;
}

void Segment3::set_p2(const Point3& p)
{
	_p2 = p;
}

double Segment3::norm() const
{
	return (_p1 - _p2).norm();
}

double Segment3::norm_square() const
{
	return (_p1 - _p2).norm_square();
}

bool Segment3::intersect(const Segment3& s, Point3& pIntersection) const
{
	// from https://paulbourke.net/geometry/pointlineplane/lineline.c
	// and https://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment

//	Calculate the line segment PaPb that is the shortest route between two lines P1P2 and P3P4.
//		Pa = P1 + mua(P2 - P1) and	Pb = P3 + mub(P4 - P3)
//		Return false if no solution exists.

	const Point3 P1 = p1();
	const Point3 P2 = p2();
	const Point3 P3 = s.p1();
	const Point3 P4 = s.p2();

	double EPS = 1.e-10;

	Point3 p13 = P1 - P3;
	Point3 p43 = P4 - P3;

	if (p43.norm_square() < EPS * EPS)
		return false;

	Point3 p21 = P2 - P1;

	if (p21.norm_square() < EPS * EPS)
		return false;

	double d4321 = p43.dot_product(p21);
	double d4343 = p43.dot_product(p43);
	double d2121 = p21.dot_product(p21);

	double denom = d2121 * d4343 - d4321 * d4321;
	if (fabs(denom) < EPS)
		return false;

	double d1321 = p13.dot_product(p21);
	double d1343 = p13.dot_product(p43);
	double numerator = d1343 * d4321 - d1321 * d4343;
	double mua = numerator / denom;

	if ((mua < 0.) || (mua > 1.))
		return false;

	pIntersection = P1 + p21 * mua; //is the nearest point on first segment, the intersection if coplanar

	// can compute the nearest point on the other segment
	// double mub = (d1343 + d4321 * mua) / d4343;
	// pIntersectionb = P3 + p43 * mub;
	//if ((mub < 0.) || (mub > 1.))
	//	return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////
Triangle3::Triangle3()
{
}

Triangle3::Triangle3(const Point3& p1, const Point3& p2, const Point3& p3) :
	_p1(p1), _p2(p2), _p3(p3)
{
}

const Point3& Triangle3::p1() const
{
	return _p1;
}

const Point3& Triangle3::p2() const
{
	return _p2;
}

const Point3& Triangle3::p3() const
{
	return _p3;
}

void Triangle3::set_p1(const Point3& p)
{
	_p1 = p;
}

void Triangle3::set_p2(const Point3& p)
{
	_p2 = p;
}

void Triangle3::set_p3(const Point3& p)
{
	_p3 = p;
}

bool Triangle3::cutted_by(const Plane3& p) const
{
	int nbPositive = 0, nbNegative = 0;

	double proj1 = p.distance_to(p1());
	if (proj1 > 0.) nbPositive++;
	if (proj1 < 0.) nbNegative++;

	double proj2 = p.distance_to(p2());
	if (proj2 > 0.) nbPositive++;
	if (proj2 < 0.) nbNegative++;

	double proj3 = p.distance_to(p3());
	if (proj3 > 0.) nbPositive++;
	if (proj3 < 0.) nbNegative++;

	return ((nbPositive > 0) && (nbNegative > 0));
}

bool Triangle3::contains(const Point3& p) const
{
	// from https://gdbooks.gitbooks.io/3dcollisions/content/Chapter4/point_in_triangle.html

	Point3 a = _p1 - p;
	Point3 b = _p2 - p;
	Point3 c = _p3 - p;

	Point3 u = b.cross_product(c);

	Point3 v = c.cross_product(a);
	if (u.dot_product(v) < 0.)
		return false;

	Point3 w = a.cross_product(b);
	if (u.dot_product(w) < 0.)
		return false;

	return true;
}

bool Triangle3::intersect_with(const Segment3& s, Point3& pIntersection) const
{
	Plane3 p(*this);

	if (p.intersect_with(s, pIntersection) == false)
		return false;

	return contains(pIntersection);
}

bool Triangle3::intersect_with(const Triangle3& t) const
{
	// first tests from https://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf

	BoundingBox3 bA(*this);
	BoundingBox3 bB(t);
	Point3 pInter;

	if (bA.intersect_with(bB) == false)
		return false;

	Plane3 planeB(t);
	if (cutted_by(planeB) == false)
		return false;

	Plane3 planeA(*this);
	if (t.cutted_by(planeA) == false)
		return false;

	//compute if any segment cut any triangles, slow but easy
	if (intersect_with(Segment3(t.p1(), t.p2()), pInter))
		return true;

	if (intersect_with(Segment3(t.p1(), t.p3()), pInter))
		return true;

	if (intersect_with(Segment3(t.p2(), t.p3()), pInter))
		return true;

	if (t.intersect_with(Segment3(p1(), p2()), pInter))
		return true;

	if (t.intersect_with(Segment3(p1(), p3()), pInter))
		return true;

	if (t.intersect_with(Segment3(p2(), p3()), pInter))
		return true;

	return false;
}

double Triangle3::surface() const
{
	return orthogonal().norm() * 0.5;
}

Point3 Triangle3::normal() const
{
	return orthogonal().normalized();
}

Point3 Triangle3::orthogonal() const
{
	return (_p1 - _p2).cross_product(_p1 - _p3);
}

///////////////////////////////////////////////////////////////////////////
Plane3::Plane3()
{
	_a = 0.; _b = 0.; _c = 0.; _d = 0.;
}

Plane3::Plane3(const Point3& p1, const Point3& p2, const Point3& p3)
{
	compute_using(p1, p2, p3);
}

Plane3::Plane3(const Triangle3& t)
{
	compute_using(t.p1(), t.p2(), t.p3());
}

void Plane3::compute_using(const Point3& p1, const Point3& p2, const Point3& p3)
{
	//compute normal using the cross product, and normalize (can be removed ?)
	Point3 pn = ((p1 - p2).cross_product(p1 - p3)).normalized();

	_a = pn._x; _b = pn._y; _c = pn._z;

	//compute _d (the plane must pass at p1)
	_d = -(_a * p1._x + _b * p1._y + _c * p1._z);
}

void Plane3::compute_using(const Triangle3& t)
{
	compute_using(t.p1(), t.p2(), t.p3());
}

double Plane3::distance_to(const Point3& p) const
{
	return _a * p._x + _b * p._y + _c * p._z + _d;
}

void Plane3::get(double& a, double& b, double& c, double& d) const
{
	a = _a; b = _b; c = _c; d = _d;
}

bool Plane3::intersect_with(const Segment3& s, Point3& pIntersection) const
{
	Point3 p1 = s.p1();
	Point3 p2 = s.p2();

	double k = _a * p1._x + _b * p1._y + _c * p1._z + _d;
	double u = _a * (p2._x - p1._x) + _b * (p2._y - p1._y) + _c * (p2._z - p1._z);

	if (u == 0.)
		return false; // no intersection, parallel

	double t = -k / u;
	if ((t <= 0.) || (t >= 1.)) //must be in the segment (not a line)
		return false;

	pIntersection._x = p1._x + t * (p2._x - p1._x);
	pIntersection._y = p1._y + t * (p2._y - p1._y);
	pIntersection._z = p1._z + t * (p2._z - p1._z);

	return true;
}

bool Plane3::intersect_with(const Plane3& p, Line3& pIntersection) const
{
	double espilon = 1.e-8;

	// compute the line direction
	Point3 direction = normal().cross_product(p.normal());
	if (direction.norm_square() < espilon * espilon)
		return false;

	//compute one intersection point

	//Plane3 p4(Point3(), this->normal() * this->_d, p.normal() * p._d);


	//todo

	return true;
}

void Plane3::project_point(const Point3& p, Point3& projected) const
{
	// from: https://stackoverflow.com/questions/9605556/how-to-project-a-point-onto-a-plane-in-3d

	projected = p - (normal() * (normal().dot_product(p) + _d));
}

Point3 Plane3::normal() const // normalized
{
	return Point3(_a, _b, _c);
}
///////////////////////////////////////////////////////////////////////////
BoundingBox3::BoundingBox3()
{
	_bInitialized = false;
	_x1 = 0.; _y1 = 0.; _z1 = 0.;
	_x2 = 0.; _y2 = 0.; _z2 = 0.;
}

BoundingBox3::BoundingBox3(const Triangle3& t)
{
	_bInitialized = false;
	add(t.p1());
	add(t.p2());
	add(t.p3());
}

void BoundingBox3::add(const Point3& p1)
{
	double x = p1._x;
	double y = p1._y;
	double z = p1._z;

	if (_bInitialized == false)
	{
		_x1 = x; _y1 = y; _z1 = z;
		_x2 = x; _y2 = y; _z2 = z;
		_bInitialized = true;
		return;
	}

	if (x < _x1)
		_x1 = x;
	else if (x > _x2)
		_x2 = x;

	if (y < _y1)
		_y1 = y;
	else if (y > _y2)
		_y2 = y;

	if (z < _z1)
		_z1 = z;
	else if (z > _z2)
		_z2 = z;
}

bool BoundingBox3::intersect_with(const BoundingBox3& b) const
{
	if (_x2 < b._x1)
		return false;

	if (_y2 < b._y1)
		return false;

	if (_z2 < b._z1)
		return false;

	if (b._x2 < _x1)
		return false;

	if (b._y2 < _y1)
		return false;

	if (b._z2 < _z1)
		return false;

	return true;
}
///////////////////////////////////////////////////////////////////////////

