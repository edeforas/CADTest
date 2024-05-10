#ifndef MeshUtil_
#define MeshUtil_

class Mesh;
class Image;
///////////////////////////////////////////////////////////////////////////
namespace MeshUtil
{
	void create_mesh_from_image(const Image& im, Mesh& m);
	void merge_vertices(Mesh& m, double dDistanceTol= 1.e-6);
	void remove_empty_triangles(Mesh& m, double dVerticeTol= 1.e-6);
}
///////////////////////////////////////////////////////////////////////////

#endif