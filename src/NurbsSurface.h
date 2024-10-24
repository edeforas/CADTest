#ifndef NurbsSurface_
#define NurbsSurface_

#include <vector>
using namespace std;

#include "Geometry.h"
class Mesh;

///////////////////////////////////////////////////////////////////////////
class NurbsSurface
{
public:
	NurbsSurface();
	virtual ~NurbsSurface();

	void clear();

	void set_degree(int degreeU,int idegreeV);
	void set_knots_u(const vector <double>& knots);
	void set_knots_v(const vector <double>& knots);
	void set_weights(const vector <double>& weights);
	void set_points(const vector <Point3>& points);

	void evaluate(double u,double v, Point3& p) const;

	void to_mesh(Mesh& m) const;
private:
	int find_knot_span(const vector <double>& knots,double u) const;

	int _degreeU, _degreeV;
	vector <double> _knotsU, _knotsV;
	vector <double> _weights;
	vector <Point3> _points;

	mutable vector<Point3> _tempPoints;
	mutable vector<double> _tempWeights;
};
///////////////////////////////////////////////////////////////////////////

#endif