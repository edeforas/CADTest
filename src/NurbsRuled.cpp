#include "NurbsRuled.h"

#include <cassert>
#include <algorithm>
using namespace std;

#include "NurbsCurve.h"
#include "NurbsSurface.h"

///////////////////////////////////////////////////////////////////////////
NurbsRuled::NurbsRuled()
{}
///////////////////////////////////////////////////////////////////////////
NurbsRuled::~NurbsRuled()
{}
///////////////////////////////////////////////////////////////////////////
bool NurbsRuled::create_ruled(const NurbsCurve& nc1, const NurbsCurve& nc2, NurbsSurface& ns) const
{
	ns.clear();

	// for now, assume degree,knots and points have equal size
	// todo
	// assume also knots are the same: todo

	vector<Point3> vp;
	vector<double> vw;

	vp = nc1.points();
	vp.insert(vp.end(), nc2.points().begin(), nc2.points().end());

	vw = nc1.weights();
	vw.insert(vw.end(), nc2.weights().begin(), nc2.weights().end());

	vector<double> knotsV = { 0., 0., 1., 1. };
	int degreeV = 1;

	ns.set_degree(nc1.degree(), degreeV);
	ns.set_knots_u(nc1.knots());
	ns.set_knots_v(knotsV);

	ns.set_weights(vw);
	ns.set_points(vp, nc1.points().size(),2);

	return true;
}
///////////////////////////////////////////////////////////////////////////