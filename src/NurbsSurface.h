#ifndef NurbsSurface_
#define NurbsSurface_

#include <vector>
using namespace std;

#include "Geometry.h"
#include "NurbsCurve.h"
class Transform;

///////////////////////////////////////////////////////////////////////////
class NurbsSurface
{
public:
	NurbsSurface();
	virtual ~NurbsSurface();

	void clear();

	void set_degree(int degreeU, int degreeV);
	int degree_u() const;
	int degree_v() const;

	void set_knots_u(const vector <double>& knots);
	void set_knots_v(const vector <double>& knots);
	void set_uniform_u();
	void set_uniform_v();
	const vector<double>& knots_u() const;
	const vector<double>& knots_v() const;

	void set_weights(const vector <double>& weights);
	void set_equals_weights(); //non rational
	const vector<double>& weights() const;
	vector<double>& weights();

	void set_closed_u(bool bClosedU);
	void set_closed_v(bool bClosedV);

	void set_points(const vector <Point3>& points, int iNbPointsU, int iNbPointsV);
	const vector<Point3>& points() const;
	vector<Point3>& points();
	int nb_points_u() const;
	int nb_points_v() const;

	void apply_transform(const Transform& t);

	bool is_closed_u() const;
	bool is_closed_v() const;

	void insert_knot_u(double u);
	void insert_knot_v(double v);

	bool degree_elevation_u();
	bool degree_elevation_v();

	void evaluate(double u, double v, Point3& p) const;

private:
	static int find_knot_span(const vector <double>& knots, double u);
	static void scale_knots(vector<double>& knots);

	void create_u_curves(vector<NurbsCurve>& vu) const;
	void create_v_curves(vector<NurbsCurve>& vv) const;

	void from_u_curves(const vector<NurbsCurve>& vu); //reuse V knots and degreee
	void from_v_curves(const vector<NurbsCurve>& vv); //reuse U knots and degreee

	int _degreeU, _degreeV;
	int _iNbPointsU, _iNbPointsV;
	bool _bClosedU, _bClosedV;

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