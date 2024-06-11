#ifndef FaceBezierTriangles_
#define FaceBezierTriangles_

#include "Mesh.h"
#include "Face.h"

///////////////////////////////////////////////////////////////////////////
class FaceBezierTriangles : public Face
{
public:
    FaceBezierTriangles();
    FaceBezierTriangles(const FaceBezierTriangles& f);
    virtual ~FaceBezierTriangles() override;
    void clear();

    virtual FaceBezierTriangles* clone() const override;
    virtual void add_to_mesh(Mesh& m, int iNbSegments) override;

protected:

};
///////////////////////////////////////////////////////////////////////////

#endif