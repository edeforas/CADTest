#ifndef _NurbsCurve_
#define _NurbsCurve_

#include <vector>
using namespace std;

#include "Geometry.h"

///////////////////////////////////////////////////////////////////////////
class NurbsCurve
{
public:
	NurbsCurve();
	virtual ~NurbsCurve();

	void clear();

	void set_degree(int degree);
	void set_knots(const vector <double>& knots);
	void set_weights(const vector <double>& weights);
	void set_points(const vector <Point3>& points);

	void insert_knot(double u);

	const vector<Point3>& points() const;
	void evaluate(double u, Point3& p) const;

	void to_polyline(vector<Point3>& polyline) const;

private:
	int find_knot_span(const vector <double>& knots,double t) const;

	int _degree;
	vector <double> _knots;
	vector <double> _weights;
	vector <Point3> _points;

	mutable vector<Point3> _tempPoints;
	mutable vector<double> _tempWeights;
};
///////////////////////////////////////////////////////////////////////////

#endif