#include "NurbsRevolve.h"

#include <cassert>
#include <algorithm>
#include <cmath>
using namespace std;

#include "NurbsCurve.h"
#include "NurbsUtil.h"
#include "NurbsSurface.h"

///////////////////////////////////////////////////////////////////////////
NurbsRevolve::NurbsRevolve()
{}
///////////////////////////////////////////////////////////////////////////
NurbsRevolve::~NurbsRevolve()
{}
///////////////////////////////////////////////////////////////////////////
bool NurbsRevolve::revolve(const NurbsCurve& nc, NurbsSurface& ns) const
{
	//only z axis and full turn for now

	//NurbsCurve refCircle;
	//NurbsUtil::create_circle(1., refCircle);

	ns.clear();
	const auto& refPoints = nc.points();

	vector<Point3> pc;
	vector<double> wc;

	//each point of nc will be transformed to a circle
	for (int i = 0; i < refPoints.size(); i++)
	{
		//todo use a circle and transforms
		double w = nc.weights()[i];

		Point3 p1 = refPoints[i];
		pc.push_back(p1);
		wc.push_back(w);
		
		Point3 p3 = p1;
		p3.x() = p1.y();
		p3.y() = -p1.x();
		Point3 p2 = p3 + p1; //diag point
		p2.z() = p1.z();
		pc.push_back(p2); 
		wc.push_back(w/sqrt(2.));
		pc.push_back(p3);
		wc.push_back(w);

		Point3 p5 = p3;
		p5.x() = p3.y();
		p5.y() = -p3.x();
		Point3 p4 = p5 + p3; //diag point
		p4.z() = p3.z();
		pc.push_back(p4);
		wc.push_back(w / sqrt(2.));
		pc.push_back(p5);
		wc.push_back(w);

		Point3 p7 = p5;
		p7.x() = p5.y();
		p7.y() = -p5.x();
		Point3 p6 = p7 + p5; //diag point
		p6.z() = p5.z();
		pc.push_back(p6);
		wc.push_back(w / sqrt(2.));
		pc.push_back(p7);
		wc.push_back(w);

		Point3 p9 = p7;
		p9.x() = p7.y();
		p9.y() = -p7.x();
		Point3 p8 = p9 + p7; //diag point
		p8.z() = p7.z();
		pc.push_back(p8);
		wc.push_back(w / sqrt(2.));
		pc.push_back(p9);
		wc.push_back(w);
	}

	ns.clear();
	ns.set_degree(2, nc.degree());
	ns.set_points(pc, 9, nc.nb_points());
	ns.set_knots_u({ 0., 0., 0., 0.25, 0.25, 0.5, 0.5, 0.75, 0.75, 1., 1., 1. }); // (refCircle.knots());
	ns.set_knots_v(nc.knots());
	ns.set_weights(wc);

	ns.set_closed_u(true);
	ns.set_closed_v(nc.is_closed()); //todo add case when nc.begin() and nc.end() are on axis

	return true;
}
///////////////////////////////////////////////////////////////////////////