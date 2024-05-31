#ifndef FaceNurbs_
#define FaceNurbs_

#include "Mesh.h"
#include "Face.h"
#include "GeometryNurbs.h"

///////////////////////////////////////////////////////////////////////////
class FaceNurbs : public Face
{
public:
    FaceNurbs();
    FaceNurbs(const FaceNurbs& f);
    virtual ~FaceNurbs() override;
    void clear();

    virtual FaceNurbs* clone() const override;
    virtual void add_to_mesh(Mesh& m, int iNbSegments) override;

protected:
    GeometryNurbs _nurbs;
};
///////////////////////////////////////////////////////////////////////////

#endif