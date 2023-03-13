#include "MeshKernelTIN.h"

#include <cassert>

///////////////////////////////////////////////////////////////////////////
TriangleTIN::TriangleTIN(int vertex1, int vertex2, int vertex3)
{
	_vertex1 = vertex1; _vertex2 = vertex2; _vertex3 = vertex3;
	bUnlinked = false;
}
///////////////////////////////////////////////////////////////////////////
VertexTIN::VertexTIN(const Point3& vertex) :
	_vertex(vertex)
{ }
///////////////////////////////////////////////////////////////////////////
MeshKernelTIN::MeshKernelTIN()
{ }

MeshKernelTIN::~MeshKernelTIN()
{
	MeshKernelTIN::clear();
}

void MeshKernelTIN::clear()
{
	_vTriangles.clear();
	_vVertices.clear();
}
///////////////////////////////////////////////////////////////////////////
int MeshKernelTIN::add_vertex(const Point3& vertex)
{
	_vVertices.push_back(VertexTIN(vertex));
	return (int)_vVertices.size() - 1;
}

void MeshKernelTIN::set_vertex(int iVertex, const Point3& vertex)
{
	assert(iVertex >= 0);
	assert(iVertex < (int)_vVertices.size());

	_vVertices[iVertex]._vertex = vertex;
}

void MeshKernelTIN::get_vertex(int iVertex, Point3& vertex) const
{
	assert(iVertex >= 0);
	assert(iVertex < (int)_vVertices.size());

	vertex = _vVertices[iVertex]._vertex;
}

int MeshKernelTIN::nb_vertices() const
{
	return (int)_vVertices.size();
}
///////////////////////////////////////////////////////////////////////////
int MeshKernelTIN::add_triangle(int iVertex1, int iVertex2, int iVertex3)
{
	// vertices should exist:
	assert(iVertex1 >= 0);
	assert(iVertex1 < (int)_vVertices.size());
	assert(iVertex2 >= 0);
	assert(iVertex2 < (int)_vVertices.size());
	assert(iVertex3 >= 0);
	assert(iVertex3 < (int)_vVertices.size());

	_vTriangles.push_back(TriangleTIN(iVertex1, iVertex2, iVertex3));

	return (int)(_vTriangles.size() - 1);
}

void MeshKernelTIN::get_triangle_vertices(int iTriangle, int& iVertex1, int& iVertex2, int& iVertex3) const
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	iVertex1 = _vTriangles[iTriangle]._vertex1;
	iVertex2 = _vTriangles[iTriangle]._vertex2;
	iVertex3 = _vTriangles[iTriangle]._vertex3;
}

void MeshKernelTIN::unlink_triangle(int iTriangle)
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	_vTriangles[iTriangle].bUnlinked = true;
}

bool MeshKernelTIN::is_triangle_unlinked(int iTriangle)
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	return _vTriangles[iTriangle].bUnlinked;
}

int MeshKernelTIN::nb_triangles() const
{
	return (int)_vTriangles.size();
}

void MeshKernelTIN::get_near_triangles(int iTriangle, int& iT1, int& iT2, int& iT3) const
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	// very slow but must add function
}



bool MeshKernelTIN::get_triangles_near_edge(int iVertex1, int  iVertex2, int& iTriangle1, int& iTriangle2) const
{
	return false;
	//todo
}

///////////////////////////////////////////////////////////////////////////

