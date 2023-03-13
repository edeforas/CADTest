#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "STLFile.h"

namespace STLFile
{
	bool save(const string& filename, const Mesh& to_mesh)
	{
		ofstream f(filename, ios::binary);
		if (!f)
			return false;

		int32_t zero = 0;
		float fzero = 0.f;

		// write header
		for (int i = 0; i < 20; i++)
			f.write((char*)(&zero), 4);

		auto iNbTriangles = to_mesh.nb_triangles();

		int iNbValidTriangles = 0;
		for (int i = 0; i < to_mesh.nb_triangles(); i++)
			if (to_mesh.is_triangle_unlinked(i) == false)
				iNbValidTriangles++;

		Triangle3 t;
		f.write((char*)(&iNbValidTriangles), 4);

		for (int i = 0; i < iNbTriangles; i++)
		{
			if (to_mesh.is_triangle_unlinked(i))
				continue;

			Point3 p1, p2, p3;
			to_mesh.get_triangle_vertices(i, p1, p2, p3);

			// write normals
			f.write((char*)(&fzero), 4);
			f.write((char*)(&fzero), 4);
			f.write((char*)(&fzero), 4);

			float p;
			p = (float)p1._x; f.write((char*)(&p), 4);
			p = (float)p1._y; f.write((char*)(&p), 4);
			p = (float)p1._z; f.write((char*)(&p), 4);

			p = (float)p2._x; f.write((char*)(&p), 4);
			p = (float)p2._y; f.write((char*)(&p), 4);
			p = (float)p2._z; f.write((char*)(&p), 4);

			p = (float)p3._x; f.write((char*)(&p), 4);
			p = (float)p3._y; f.write((char*)(&p), 4);
			p = (float)p3._z; f.write((char*)(&p), 4);

			f.write((char*)(&zero), 2);
		}
		return true;
	}
	///////////////////////////////////////////////////////////////////////////
	bool load(const string& filename, Mesh& to_mesh)
	{
		to_mesh.clear();
		ifstream f(filename, ios::binary);
		if (!f)
			return false;

		//ignore header
		int32_t tmp = 0;
		for (int i = 0; i < 20; i++)
			f.read((char*)(&tmp), 4);

		int32_t nbFacet = 0;
		f.read((char*)(&nbFacet), 4);

		// read facets
		float p1x = 0.f, p1y = 0.f, p1z = 0.f;
		float p2x = 0.f, p2y = 0.f, p2z = 0.f;
		float p3x = 0.f, p3y = 0.f, p3z = 0.f;
		float ftmp = 0.f;
		for (int i = 0; i < nbFacet; i++)
		{
			//ignore normal
			f.read((char*)(&ftmp), 4);
			f.read((char*)(&ftmp), 4);
			f.read((char*)(&ftmp), 4);

			//read points
			f.read((char*)(&p1x), 4);
			f.read((char*)(&p1y), 4);
			f.read((char*)(&p1z), 4);
			f.read((char*)(&p2x), 4);
			f.read((char*)(&p2y), 4);
			f.read((char*)(&p2z), 4);
			f.read((char*)(&p3x), 4);
			f.read((char*)(&p3y), 4);
			f.read((char*)(&p3z), 4);

			//ignore color
			f.read((char*)(&tmp), 2);

			to_mesh.add_vertex(p1x, p1y, p1z);
			to_mesh.add_vertex(p2x, p2y, p2z);
			to_mesh.add_vertex(p3x, p3y, p3z);
			to_mesh.add_triangle(to_mesh.nb_vertices() - 3, to_mesh.nb_vertices() - 2, to_mesh.nb_vertices() - 1);
		}

		return true;
	}
	///////////////////////////////////////////////////////////////////////////
}