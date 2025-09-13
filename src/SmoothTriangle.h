#ifndef SmoothTriangle_
#define SmoothTriangle_

#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////
class SmoothTriangle
{
public:
    class SmoothTriangle();
    virtual ~SmoothTriangle();

    void set_points(const Point3& P1, const Point3& P2, const Point3& P3);
    void set_control_P(const Point3& controlP1P2, const Point3& controlP1P3, const Point3& controlP2P3);

    Point3 eval(double s, double u, double v = -1.) const;

    virtual void to_mesh(Mesh& m, int iNbSegments) const;

protected:
    Point3 _P1, _P2, _P3;
    Point3 _controlP1P2;
    Point3 _controlP1P3;
    Point3 _controlP2P3;
};
///////////////////////////////////////////////////////////////////////////

#endif