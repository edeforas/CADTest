#include "MeshUtil.h"
#include "ImageUtil.h"

#include "Image.h"
#include "Mesh.h"

#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std; 

///////////////////////////////////////////////////////////////////////////
void MeshUtil::create_mesh_from_image(const Image& im, Mesh& m)
{
	m.clear();
	Image imBW;

	ImageUtil::convert_to_bw(im, imBW);

	for (int i = 0; i < imBW.width() - 1; i++)
		for (int j = 0; j < imBW.height() - 1; j++)
			m.add_quad(Point3(i, j, imBW(i, j)), Point3(i+1, j, imBW(i+1, j)), Point3(i + 1, j+1, imBW(i+1, j+1)), Point3(i , j+1, imBW(i, j+1)));
}
///////////////////////////////////////////////////////////////////////////
void MeshUtil::merge_vertices(Mesh& m,double dDistanceTol)
{
	// for now a very slow N**2 algorithm
	// TODO: use quick sort along an axis and use a infinite norm to bound search range
	int iNbVertices = m.nb_vertices();
	double dDistanceTolSq = dDistanceTol * dDistanceTol;
	vector<int> verticesAlias(iNbVertices, -1); //-1 means keep vertice else this is the vertice alias id

	for (int i = 0; i < iNbVertices; i++)
	{
		Point3 v1, v2;
		m.get_vertex(i, v1);
		for (int j = 0; j < i; j++)
		{
			if (verticesAlias[j] >= 0)
				continue; // Point is already an alias

			m.get_vertex(j, v2);
			double distSq = v1.distance_square(v2);
			if (distSq < dDistanceTolSq)
			{
				verticesAlias[i] = j; //alias found
				continue;
			}
		}
	}

	// replace vertices by reconstructing mesh
	Mesh mOld = m;
	m.clear();

	//readd,reindex the vertices
	for (int i = 0; i < verticesAlias.size(); i++)
	{
		if (verticesAlias[i] == -1)
		{
			Point3 p;
			mOld.get_vertex(i, p);
			int iV = m.add_vertex(p);
			verticesAlias[i] = iV;
		}
		else
		{
			int iAlias = verticesAlias[verticesAlias[i]];
			verticesAlias[i] = iAlias;
		}
	}

	//readd the triangles
	for (int i = 0; i < mOld.nb_triangles(); i++)
	{
		if (mOld.is_triangle_unlinked(i))
			continue;

		int i1, i2, i3;
		int newI1, newI2, newI3;

		mOld.get_triangle_vertices(i, i1, i2, i3);
		newI1 = verticesAlias[i1];
		newI2 = verticesAlias[i2];
		newI3 = verticesAlias[i3];

		assert(newI1 < m.nb_vertices());
		assert(newI2 < m.nb_vertices());
		assert(newI3 < m.nb_vertices());

		m.add_triangle(newI1, newI2, newI3);
	}
}
///////////////////////////////////////////////////////////////////////////
void MeshUtil::remove_empty_triangles(Mesh& m, double dVerticeTol)
{
	for (int i = 0; i < m.nb_triangles(); i++)
	{
		if (m.is_triangle_unlinked(i))
			continue;

		Point3 p1, p2, p3;
		m.get_triangle_vertices(i, p1, p2, p3);

		if ((p1 - p2).norm_square() < dVerticeTol * dVerticeTol)
		{
			m.unlink_triangle(i);
			continue;
		}

		if ((p2 - p3).norm_square() < dVerticeTol * dVerticeTol)
		{
			m.unlink_triangle(i);
			continue;
		}

		if ((p3 - p1).norm_square() < dVerticeTol * dVerticeTol)
		{
			m.unlink_triangle(i);
			continue;
		}
	}
}
///////////////////////////////////////////////////////////////////////////