#ifndef MeshKernel_
#define MeshKernel_

#include "Geometry.h"

///////////////////////////////////////////////////////////////////////////
class MeshKernel
{
public:
    MeshKernel();
    virtual ~MeshKernel();
    virtual void clear() =0;

    //vertices management
    virtual int nb_vertices() const =0; // return the vertex id
    virtual int add_vertex(const Point3& vertex) =0; // return the vertex id
    virtual void set_vertex(int iVertex, const Point3& vertex) =0;
    virtual void get_vertex(int iVertex, Point3& vertex) const =0;

    //triangles management
    virtual int nb_triangles() const =0;
	virtual int add_triangle(int iVertex1, int iVertex2, int iVertex3) =0; // return the triangle id
    virtual void get_triangle_vertices(int iTriangle, int& iVertex1, int& iVertex2, int& iVertex3) const =0;
    virtual void unlink_triangle(int iTriangle) =0;
    virtual bool is_triangle_unlinked(int iTriangle) = 0;

    //spatial relations
    virtual void get_near_triangles(int iTriangle, int& iT1, int& iT2, int& iT3) const = 0;
    virtual bool get_triangles_near_edge(int iVertex1,int  iVertex2, int& iTriangle1, int& iTriangle2) const=0;
};
///////////////////////////////////////////////////////////////////////////

#endif