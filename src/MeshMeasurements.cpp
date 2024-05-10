#include "MeshMeasurements.h"

#include <cassert>

#include "Mesh.h"
#include "Geometry.h"

bool MeshMeasurements::has_no_self_intersections(const Mesh& m)
{
	// todo
	return true;
}

bool MeshMeasurements::has_no_degenerated_triangles(const Mesh& m)
{
	//test degenerated faces
	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (m.is_triangle_unlinked(i) == true)
			continue;

		Triangle3 t;
		m.get_triangle(i, t);
		if (t.surface() == 0) // todo epsilon
			return false;
	}

	return true;
}

bool MeshMeasurements::is_closed(const Mesh& m)
{
	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (m.is_triangle_unlinked(i))
			continue;

		int t1, t2, t3;
		m.get_near_triangles(i, t1, t2, t3);
		if ((t1 == -1) || (t2 == -1) || (t3 == -1))
			return false;
	}

	return true;
}

bool MeshMeasurements::is_oriented_outside(const Mesh& m)
{
	return MeshMeasurements::volume(m) >= 0;
}

bool MeshMeasurements::is_clean(const Mesh& m)
{
	if (has_no_degenerated_triangles(m) == false)
		return false;

	if (is_oriented_outside(m) == false)
		return false;

	if (is_closed(m) == false)
		return false;

	if (has_no_self_intersections(m) == false)
		return false;

	if (has_no_isolated_vertices(m) == false)
		return false;

	if (has_no_duplicated_vertices(m) == false)
		return false;

	if (has_no_short_edges(m) == false)
		return false;

	if (has_no_self_intersections(m) == false)
		return false;

	return true;
}

double MeshMeasurements::volume(const Mesh& m)
{
	// volume computed using: https://mathworld.wolfram.com/PolyhedronVolume.html

	double volume = 0.;
	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (m.is_triangle_unlinked(i))
			continue;

		Triangle3 t;
		m.get_triangle(i, t);
		volume += t.p1().dot_product(t.orthogonal());
	}

	return volume / 6.;
}

double MeshMeasurements::surface(const Mesh& m)
{
	// surface computed using: https://math.stackexchange.com/questions/128991/how-to-calculate-the-area-of-a-3d-triangle

	double surface = 0.;
	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (m.is_triangle_unlinked(i))
			continue;

		Triangle3 t;
		m.get_triangle(i, t);
		surface += t.surface();
	}

	return surface;
}

bool MeshMeasurements::has_no_isolated_vertices(const Mesh& m)
{
	return true; //todo
}
bool MeshMeasurements::has_no_duplicated_vertices(const Mesh& m)
{
	return true; //todo
}

bool MeshMeasurements::has_no_short_edges(const Mesh& m)
{
	return true; //todo
}
