#ifndef MeshKernelHalfEdge_
#define MeshKernelHalfEdge_

#include <vector>
using namespace std;

#include "MeshKernel.h"
#include "Geometry.h"

///////////////////////////////////////////////////////////////////////////
// HalfEdge struct as in :https://jerryyin.info/geometry-processing-algorithms/half-edge/

class TriangleHalfEdge
{
public:
	TriangleHalfEdge();

	int halfEdge;
	bool bUnlinked;
};

class HalfEdge
{
public:
	HalfEdge();
	int originVertex;

	int halfEdgePair;
	int triangle;
	int nextHalfEdge;
	int prevHalfEdge;

};

class VertexHalfEdge
{
public:
	VertexHalfEdge();
	explicit VertexHalfEdge(const Point3& p);

	Point3 vertex;
	int halfEdge;
};

///////////////////////////////////////////////////////////////////////////
class MeshKernelHalfEdge : public MeshKernel
{
public:
	MeshKernelHalfEdge();
	virtual ~MeshKernelHalfEdge() override;
	virtual void clear() override;

	virtual int nb_vertices() const override; // return the vertice id
	virtual int add_vertex(const Point3& vertex) override;
	virtual void set_vertex(int iVertex, const Point3& vertex) override;
	virtual void get_vertex(int iVertex, Point3& vertex) const override;

	virtual int nb_triangles() const override;
	virtual int add_triangle(int iVertex1, int iVertex2, int iVertex3) override; // return the triangle id
	virtual void get_triangle_vertices(int iTriangle, int& iVertex1, int& iVertex2, int& iVertex3) const override;
	virtual void unlink_triangle(int iTriangle) override;
	virtual bool is_triangle_unlinked(int iTriangle) override;

	virtual void get_near_triangles(int iTriangle, int& iT1, int& iT2, int& iT3) const override;
	virtual bool get_triangles_near_edge(int iVertex1, int  iVertex2, int& iTriangle1, int& iTriangle2) const override;

private:
	vector<TriangleHalfEdge> _vTriangles;
	vector<VertexHalfEdge> _vVertices;
	vector<HalfEdge> _vHalfEdges;
};
///////////////////////////////////////////////////////////////////////////

#endif