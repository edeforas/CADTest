#include "MeshBoolean.h"
#include <cassert>

MeshBoolean::MeshBoolean()
{ }

void MeshBoolean::split_meshes(const Mesh& A, const Mesh& B, Mesh& Aoutside, Mesh& Boutside, Mesh& AInB, Mesh& BInA)
{
	Aoutside = A;
	Boutside = B;

	//slow, for now
	for (int i = 0; i < A.nb_triangles(); i++)
	{
		if (A.is_triangle_unlinked(i))
			continue;

		Triangle3 tA;
		A.get_triangle(i, tA);
		BoundingBox3 bboxA(tA);

		for (int j = 0; j < B.nb_triangles(); j++)
		{
			if (B.is_triangle_unlinked(j))
				continue;

			Triangle3 tB;
			B.get_triangle(j, tB);
			BoundingBox3 bboxB(tB); // slow: we recompute the bbox each time

			if (bboxA.intersect_with(bboxB) == false)
				continue;

			// triangles tA and tB, are valid, and may cut
			Aoutside.split_triangle(i, tB);
			Boutside.split_triangle(j, tA);
		}
	}
}
///////////////////////////////////////////////////////////////////////////