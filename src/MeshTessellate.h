#ifndef _MeshTessellate_
#define _MeshTessellate_

#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////
class MeshTessellate
{
public:
    MeshTessellate();
    virtual ~MeshTessellate();

    void compute(const Mesh & meshIn, int iNbSegments, Mesh& meshOut);

private:
    Point3 interpolate(const Point3& a, const Point3& b, const Point3& c, int uStep, int vStep, int maxStep);

};
///////////////////////////////////////////////////////////////////////////

#endif