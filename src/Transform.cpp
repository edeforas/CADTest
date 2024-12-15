#include "Transform.h"

#include <cmath>

///////////////////////////////////////////////////////////////////////////
Transform::Transform()
{ }

void Transform::reset()
{
	_translation = Point3(0., 0., 0.);
}

void Transform::apply(vector<Point3>& v) const
{
	for (auto& p : v)
		apply(p);
}

void Transform::apply(Point3& p) const
{
	p += _translation; //todo rotation
}

void Transform::set_global_translation(const Point3& translation)
{
	_translation = translation;
}

void Transform::set_global_translation(double x, double y, double z)
{
	_translation = Point3(x, y, z);
}

///////////////////////////////////////////////////////////////////////////