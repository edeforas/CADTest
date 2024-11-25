#include "Transform.h"

Transform::Transform()
{ }

void Transform::reset()
{
	_translation = Point3(0., 0., 0.);
}

void Transform::apply(Mesh& m)
{
	for (int i = 0; i < m.nb_vertices(); i++)
	{
		// todo optimize
		Point3 pv;
		m.get_vertex(i, pv);
		pv += _translation;
		m.set_vertex(i, pv);
	}
}

void Transform::apply(vector<Point3>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i] += _translation;
	}
}

void Transform::set_global_translation(const Point3& translation)
{
	_translation = translation;
}

void Transform::set_global_translation(double x, double y, double z)
{
	_translation = Point3(x, y, z);
}
