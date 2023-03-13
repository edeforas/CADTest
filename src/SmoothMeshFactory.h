#ifndef _SmoothMeshFactory_
#define _SmoothMeshFactory_

#include "SmoothMesh.h"

namespace SmoothMeshFactory
{
	
    void create_tetrahedron(double dSize, SmoothMesh& m);
    void create_box(double xSize, double ySize, double zSize, SmoothMesh& m);
    void create_octahedron(double dSize, SmoothMesh& m);
    void create_dodecahedron(double dSize, SmoothMesh& m);
    void create_icosahedron(double dSize, SmoothMesh& m);
    void create_sphere(double dRadius, SmoothMesh& m);

    /*
    void create_cylinder(double dHeight, double dRadius,int iNbSegments, SmoothMesh& m);
    void create_torus(double dMajorRadius, double dMinorRadius, int iNbSegments, SmoothMesh& m);
	*/
}
#endif