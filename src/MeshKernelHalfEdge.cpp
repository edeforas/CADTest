#include "MeshKernelHalfEdge.h"

#include <cassert>

///////////////////////////////////////////////////////////////////////////
VertexHalfEdge::VertexHalfEdge()
{
	halfEdge = -1; // not associated
}
VertexHalfEdge::VertexHalfEdge(const Point3& p) :
	vertex(p)
{
	halfEdge = -1; // not associated
}
TriangleHalfEdge::TriangleHalfEdge()
{
	halfEdge = -1; // not associated
	bUnlinked = false;
}
HalfEdge::HalfEdge()
{
	originVertex = -1;
	halfEdgePair = -1;
	triangle = -1;
	nextHalfEdge = -1;
	prevHalfEdge = -1;
}
///////////////////////////////////////////////////////////////////////////
MeshKernelHalfEdge::MeshKernelHalfEdge()
{ }

MeshKernelHalfEdge::~MeshKernelHalfEdge()
{ }

void MeshKernelHalfEdge::clear()
{
	_vTriangles.clear();
	_vVertices.clear();
	_vHalfEdges.clear();
}
////////////////////////////////////////////////////////////////////////////
int MeshKernelHalfEdge::nb_vertices() const
{
	return (int)_vVertices.size();
}

int MeshKernelHalfEdge::add_vertex(const Point3& vertex)
{
	_vVertices.push_back(VertexHalfEdge(vertex));
	return (int)_vVertices.size() - 1;
}

void MeshKernelHalfEdge::set_vertex(int iVertex, const Point3& vertex)
{
	assert(iVertex < (int)_vVertices.size());
	_vVertices[iVertex].vertex = vertex;
}

void MeshKernelHalfEdge::get_vertex(int iVertex, Point3& vertex) const
{
	assert(iVertex < (int)_vVertices.size());
	vertex = _vVertices[iVertex].vertex;
}

////////////////////////////////////////////////////////////////////////////

int MeshKernelHalfEdge::nb_triangles() const
{
	return (int)_vTriangles.size();
}

void MeshKernelHalfEdge::get_triangle_vertices(int iTriangle, int& iVertex1, int& iVertex2, int& iVertex3) const
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	int HF1 = _vTriangles[iTriangle].halfEdge;
	iVertex1 = _vHalfEdges[HF1].originVertex;

	int HF2 = _vHalfEdges[HF1].nextHalfEdge;
	iVertex2 = _vHalfEdges[HF2].originVertex;

	int HF3 = _vHalfEdges[HF2].nextHalfEdge;
	iVertex3 = _vHalfEdges[HF3].originVertex;

	assert(_vHalfEdges[HF3].nextHalfEdge == HF1); //only allowing triangles
}

void MeshKernelHalfEdge::unlink_triangle(int iTriangle)
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	// unlink triangle
	int iEdge0 = _vTriangles[iTriangle].halfEdge;
	_vHalfEdges[iEdge0].triangle = -1;

	int iEdge1 = _vHalfEdges[iEdge0].nextHalfEdge;
	_vHalfEdges[iEdge1].triangle = -1;

	int iEdge2 = _vHalfEdges[iEdge1].nextHalfEdge;
	_vHalfEdges[iEdge2].triangle = -1;

	assert(_vHalfEdges[iEdge2].nextHalfEdge == iEdge0);

	_vTriangles[iTriangle].bUnlinked = true;
}

bool MeshKernelHalfEdge::is_triangle_unlinked(int iTriangle)
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	return _vTriangles[iTriangle].bUnlinked;
}

int MeshKernelHalfEdge::add_triangle(int iVertex1, int iVertex2, int iVertex3)
{
	// create edges

	// add edges

	// add face 

	// link to edges

	int iTriangle = (int)(_vTriangles.size() - 1); // return the new iTriangle
	return iTriangle;
}

void MeshKernelHalfEdge::get_near_triangles(int iTriangle, int& iT1, int& iT2, int& iT3) const
{
	assert(iTriangle >= 0);
	assert(iTriangle < (int)_vTriangles.size());

	int iEdge0 = _vTriangles[iTriangle].halfEdge;
	iT1 = _vHalfEdges[_vHalfEdges[iEdge0].halfEdgePair].triangle;

	int iEdge1 = _vHalfEdges[iEdge0].nextHalfEdge;
	iT2 = _vHalfEdges[_vHalfEdges[iEdge0].halfEdgePair].triangle;

	int iEdge2 = _vHalfEdges[iEdge1].nextHalfEdge;
	iT3 = _vHalfEdges[_vHalfEdges[iEdge1].halfEdgePair].triangle;

	assert(_vHalfEdges[iEdge2].nextHalfEdge == iEdge0);
}

bool MeshKernelHalfEdge::get_triangles_near_edge(int iVertex1, int  iVertex2, int& iTriangle1, int& iTriangle2) const
{
	//todo

	return false;
}

////////////////////////////////////////////////////////////////////////////

