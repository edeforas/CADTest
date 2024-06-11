#ifndef FaceBezierPatches
#define FaceBezierPatches_

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
    FaceBezierPatches(const FaceBezierPatches& f);
    virtual ~FaceBezierPatches() override;
    void clear();

    virtual FaceBezierPatches* clone() const override;

    void set_points(const vector<Point3>& vP);

    virtual void add_to_mesh(Mesh& m, int iNbSegments) override;

protected:
    vector<Point3> _vP;

};
///////////////////////////////////////////////////////////////////////////

#endif