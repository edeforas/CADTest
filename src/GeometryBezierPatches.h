#ifndef SurfaceBezierPatches_
#define SurfaceBezierPatches_

#include "Face.h"
#include "Mesh.h"

#include "Geometry.h"
#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////
class FaceBezierPatches : public Face
{
public:
    FaceBezierPatches();
    virtual ~FaceBezierPatches();
    void clear();

    void set_points(const vector<Point3>& vP);

    virtual void add_to_mesh(Mesh& m, int iNbSegments) override;

protected:
    vector<Point3> _vP;

};
///////////////////////////////////////////////////////////////////////////

#endif