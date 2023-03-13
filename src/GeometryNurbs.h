#ifndef GeometryNurbs_
#define GeometryNurbs_

#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////
class GeometryNurbs
{
public:
    GeometryNurbs();
    virtual ~GeometryNurbs();
    void clear();

    virtual void add_to_mesh(Mesh& m, int iNbSegments);

protected:
};
///////////////////////////////////////////////////////////////////////////

#endif