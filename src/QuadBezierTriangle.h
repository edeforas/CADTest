#ifndef QuadBezierTriangle_
#define QuadBezierTriangle_

#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////
class QuadBezierTriangle
{
public:
	QuadBezierTriangle();
	virtual ~QuadBezierTriangle();

	void set_points(const Point3& P1, const Point3& P2, const Point3& P3); //also create middle control points
	void set_control_points(const Point3& controlP1P2, const Point3& controlP1P3, const Point3& controlP2P3);
	void set_weights(double wP1, double wP2, double wP3, double wP1P2, double wP1P3, double wP2P3);

	Point3 eval(double s, double u, double v = -1.) const;

	virtual void add_to_mesh(Mesh& m, int iNbSegments) const;

	void apply_transform(const Transform& t);

protected:
	Point3 _P1, _P2, _P3;
	Point3 _controlP1P2;
	Point3 _controlP1P3;
	Point3 _controlP2P3;

	double _wP1, _wP2, _wP3;
	double _wP1P2, _wP1P3, _wP2P3;
};
///////////////////////////////////////////////////////////////////////////

#endif