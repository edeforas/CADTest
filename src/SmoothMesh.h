#ifndef SmoothMesh_
#define SmoothMesh_

#include "Geometry.h"
#include "QuadBezierTriangle.h"

#include <vector>
using namespace std;

class Transform;
class Mesh;

///////////////////////////////////////////////////////////////////////////
class SmoothMesh
{
public:
    SmoothMesh();
    SmoothMesh(const SmoothMesh & m);
    virtual ~SmoothMesh();

    SmoothMesh& operator=(const SmoothMesh& m);
    void add_mesh(const SmoothMesh& vst);
	
	void add_triangle(const QuadBezierTriangle& st);
    const QuadBezierTriangle& triangle(int i) const;
	int nb_triangles() const;

    void add_to_mesh(Mesh& m,int iNbSegments) const;

    void apply_transform(const Transform& t);

    void add_flat_triangle(const Point3& p1, const  Point3& p2, const Point3& p3);
    void add_flat_quad(const Point3& p1, const  Point3& p2, const Point3& p3, const Point3& p4);
    void add_flat_pentagon(const Point3& p1, const  Point3& p2, const Point3& p3, const Point3& p4, const Point3& p5);


/*
    int nb_vertices() const;
    int add_vertex(const Point3& vertex);
    int add_vertex(double a, double b, double c);
    void set_vertex(int iVertex, const Point3& vertex);
    void get_vertex(int iVertex, Point3& vertex) const;

    int add_triangle(int iVertex1, int iVertex2, int iVertex3); // return the triangle ID
    int add_triangle(const Point3& p1, const  Point3& p2, const Point3& p3); //helper
    void get_triangle(int iTriangle, Triangle3& f) const;
    void get_triangle_vertices(int iTriangle, int& iVertex1, int& iVertex2, int& iVertex3) const;
    void get_triangle_vertices(int iTriangle, Point3& p1, Point3& p2, Point3& p3) const;

    void unlink_triangle(int iTriangle);
    bool is_triangle_unlinked(int iTriangle) const;
    void get_near_triangles(int iTriangle, int& iT1, int& iT2, int& iT3) const;

    void split_triangle_with_vertex(int iTriangle, const Point3& p);
    void split_triangle_with_vertex(int iTriangle, int iVertex); //create 3 triangles with edges and new vertex, remove iTriangle
    void split_edge_with_vertex(int iTriangle1, int iTriangle2,int iVertex1, int iVertex2, int iVertexSplit); // 4 new triangles added at the end, unlink the two previous faces
    void split_triangle(int iTriangle, const Triangle3& tSplitter);

    void flip_triangle(int iTriangle); //flip triangle so normal is reversed

    void add_quad(const Point3& p1, const  Point3& p2, const Point3& p3, const Point3& p4,bool bOptimSurface = true); //helper

    void add_pentagon(int iVertex1, int iVertex2, int iVertex3, int iVertex4, int iVertex5);      
*/

    void clear();
    bool empty() const;

private:
	vector<QuadBezierTriangle> _vst;
};
///////////////////////////////////////////////////////////////////////////

#endif