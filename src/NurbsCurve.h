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
	void create_from_points(const vector<Point3>& points, int degree); //no rational, uniform

	void clear();

	void set_degree(int degree);
	int degree() const;

	void set_knots(const vector <double>& knots);
	const vector<double>& knots() const;
	void set_uniform();

	void set_weights(const vector <double>& weights);
	const vector<double>& weights() const;
	void set_equals_weights(); //non rational

	void set_points(const vector <Point3>& points);

	void insert_knot(double u);

	const vector<Point3>& points() const;
	vector<Point3>& points();
	void evaluate(double u, Point3& p) const;

	void to_polyline(vector<Point3>& polyline) const;

	static int find_knot_span(const vector <double>& knots,double t);

private:
	int _degree;
	vector <double> _knots;
	vector <double> _weights;
	vector <Point3> _points;
	int _iNbPoints;

	mutable vector<Point3> _tempPoints;
	mutable vector<double> _tempWeights;
};
///////////////////////////////////////////////////////////////////////////

#endif