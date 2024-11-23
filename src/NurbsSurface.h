#ifndef NurbsSurface_
#define NurbsSurface_

#include <vector>
using namespace std;

#include "Geometry.h"

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
	void set_uniform_u();
	void set_uniform_v();

	void set_weights(const vector <double>& weights);
	void set_equals_weights(); //non rational

	void set_points(const vector <Point3>& points, int iNbPointsU, int iNbPointsV);
	const vector<Point3>& points() const;
	int nb_points_u() const;
	int nb_points_v() const;

	void evaluate(double u,double v, Point3& p) const;

private:
	static int find_knot_span(const vector <double>& knots,double u);

	int _degreeU, _degreeV;
	int _iNbPointsU, _iNbPointsV;

	vector <double> _knotsU, _knotsV;
	vector <double> _weights;
	vector <Point3> _points;

	mutable vector<Point3> _tempPointsU;
	mutable vector<Point3> _tempPointsV;
	mutable vector<double> _tempWeightsU;
	mutable vector<double> _tempWeightsV;
};
///////////////////////////////////////////////////////////////////////////

#endif