#include "NurbsSurface.h"
#include "Mesh.h"
#include "Transform.h"

#include <cassert>
#include <algorithm>
using namespace std;

#include "NurbsCurve.h"

///////////////////////////////////////////////////////////////////////////
NurbsSurface::NurbsSurface() :
	_degreeU(0), _degreeV(0), _iNbPointsU(0), _iNbPointsV(0), _bClosedU(false), _bClosedV(false)
{
}

NurbsSurface::~NurbsSurface()
{
}

void NurbsSurface::clear()
{
	_degreeU = 0;
	_degreeV = 0;
	_knotsU.clear();
	_knotsV.clear();
	_weights.clear();
	_points.clear();
	_iNbPointsU = 0;
	_iNbPointsV = 0;
}

void NurbsSurface::set_degree(int degreeU, int degreeV)
{
	_degreeU = degreeU;
	_degreeV = degreeV;

	_tempPointsU.resize(degreeU + 1);
	_tempPointsV.resize(degreeV + 1);
	_tempWeightsU.resize(degreeU + 1);
	_tempWeightsV.resize(degreeV + 1);
}

int NurbsSurface::degree_u() const
{
	return _degreeU;
}

int NurbsSurface::degree_v() const
{
	return _degreeV;
}

void NurbsSurface::set_knots_u(const vector <double>& knots)
{
	_knotsU = knots;
	scale_knots(_knotsU);
}

void NurbsSurface::set_uniform_u()
{
	vector <double> knots;

	knots.clear();

	for (int i = 0; i <= _degreeU; i++)
		knots.push_back(0.);

	for (int i = 1; i < _iNbPointsU - _degreeU; i++)
		knots.push_back(i);

	for (int i = 0; i <= _degreeU; i++)
		knots.push_back(_iNbPointsU - _degreeU);

	set_knots_u(knots);
}

void NurbsSurface::set_knots_v(const vector <double>& knots)
{
	_knotsV = knots;
	scale_knots(_knotsV);
}

void NurbsSurface::set_uniform_v()
{
	vector <double> knots;

	for (int i = 0; i <= _degreeV; i++)
		knots.push_back(0.);

	for (int i = 1; i < _iNbPointsV - _degreeV; i++)
		knots.push_back(i);

	for (int i = 0; i <= _degreeV; i++)
		knots.push_back(_iNbPointsV - _degreeV);

	set_knots_v(knots);
}

const vector<double>& NurbsSurface::knots_u() const
{
	return _knotsU;
}
const vector<double>& NurbsSurface::knots_v() const
{
	return _knotsV;
}

void NurbsSurface::scale_knots(vector<double>& knots)
{
	//compute min and max
	double dMin = knots[0];
	double dMax = knots[0];
	for (int i = 1; i < knots.size(); i++)
	{
		double v = knots[i];
		dMin = min(dMin, v);
		dMax = max(dMax, v);
	}

	//apply scale so that 0<= knots <= 1
	for (int i = 0; i < knots.size(); i++)
		knots[i] = (knots[i] - dMin) / (dMax - dMin);
}

void NurbsSurface::set_weights(const vector <double>& weights)
{
	_weights = weights;
}

void NurbsSurface::set_equals_weights() //non rational
{
	_weights.resize(_points.size(), 1.);
}

const vector<double>& NurbsSurface::weights() const
{
	return _weights;
}

vector<double>& NurbsSurface::weights()
{
	return _weights;
}

void NurbsSurface::set_points(const vector <Point3>& points, int iNbPointsU, int iNbPointsV)
{
	_points = points;
	_iNbPointsU = iNbPointsU;
	_iNbPointsV = iNbPointsV;
}

int NurbsSurface::nb_points_u() const
{
	return _iNbPointsU;
}

int NurbsSurface::nb_points_v() const
{
	return _iNbPointsV;
}

void NurbsSurface::apply_transform(const Transform& t)
{
	for (int i = 0; i < _points.size(); i++)
	{
		// todo optimize
		Point3 pv;
		t.apply(_points[i]);
	}
}





void NurbsSurface::set_closed_u(bool bClosedU)
{
	_bClosedU = bClosedU;
}

void NurbsSurface::set_closed_v(bool bClosedV)
{
	_bClosedV = bClosedV;
}

bool NurbsSurface::is_closed_u() const
{
	return _bClosedU;
}

bool NurbsSurface::is_closed_v() const
{
	return _bClosedV;
}

const vector<Point3>& NurbsSurface::points() const
{
	return _points;
}

vector<Point3>& NurbsSurface::points()
{
	return _points;
}

int NurbsSurface::find_knot_span(const vector <double>& knots, double t)
{
	if (knots.size() < 2)
		return 0;

	if (t < 0.)
		t = 0.;

	if (t > 1.)
		t = 1.;

	//simple linear search for now
	for (int i = 0; i < knots.size() - 1; i++)
	{
		if (t < 1.)
		{
			if ((t >= knots[i]) && (t < knots[i + 1]))
				return i;
		}
		else
		{
			if ((t > knots[i]) && (t <= knots[i + 1]))
				return i;
		}
	}

	return -1; // should never be here
}

void NurbsSurface::insert_knot_u(double u)
{
	vector<NurbsCurve> vu;
	create_u_curves(vu);

	for (int i = 0; i < vu.size(); i++)
		vu[i].insert_knot(u);

	from_u_curves(vu);
}

void NurbsSurface::insert_knot_v(double v)
{
	vector<NurbsCurve> vv;
	create_v_curves(vv);

	for (int i = 0; i < vv.size(); i++)
		vv[i].insert_knot(v);

	from_v_curves(vv);
}

bool NurbsSurface::degree_elevation_u()
{
	if (_degreeU >= 3)
		return false; //only deg <=3 are handled

	vector<NurbsCurve> vu;
	create_u_curves(vu);

	for (int i = 0; i < vu.size(); i++)
		vu[i].degree_elevation();

	from_u_curves(vu);
	return true;
}

bool NurbsSurface::degree_elevation_v()
{
	if (_degreeV >= 3)
		return false; //only deg <=3 are handled

	vector<NurbsCurve> vv;
	create_v_curves(vv);

	for (int i = 0; i < vv.size(); i++)
		vv[i].degree_elevation();

	from_v_curves(vv);
	return true;
}

void NurbsSurface::create_u_curves(vector<NurbsCurve>& vu) const
{
	vu.clear();

	for (int v = 0; v < nb_points_v(); v++)
	{
		NurbsCurve n;
		n.set_degree(_degreeU);
		n.set_knots(_knotsU);

		vector<Point3> vp;
		vector<double> vw;
		for (int u = 0; u < nb_points_u(); u++)
		{
			vp.push_back(points()[u + nb_points_u() * v]);
			vw.push_back(weights()[u + nb_points_u() * v]);
		}

		n.set_points(vp);
		n.set_weights(vw);
		vu.push_back(n);
	}
}

void NurbsSurface::create_v_curves(vector<NurbsCurve>& vv) const
{
	vv.clear();

	for (int u = 0; u < nb_points_u(); u++)
	{
		NurbsCurve n;
		n.set_degree(_degreeV);
		n.set_knots(_knotsV);

		vector<Point3> vp;
		vector<double> vw;
		for (int v = 0; v < nb_points_v(); v++)
		{
			vp.push_back(points()[u + nb_points_u() * v]);
			vw.push_back(weights()[u + nb_points_u() * v]);
		}

		n.set_points(vp);
		n.set_weights(vw);
		vv.push_back(n);
	}
}

void NurbsSurface::from_u_curves(const vector<NurbsCurve>& vu) //reuse V knots and degree
{
	if (vu.empty())
		return;

	//update knots
	set_knots_u(vu[0].knots());

	//update_points
	vector<Point3> vp;
	vector<double> vw;
	for (int v = 0; v < vu.size(); v++)
	{
		vp.insert(vp.end(), vu[v].points().begin(), vu[v].points().end());
		vw.insert(vw.end(), vu[v].weights().begin(), vu[v].weights().end());
	}
	set_points(vp, vu[0].nb_points(), nb_points_v());
	set_weights(vw);
	set_degree(vu[0].degree(), degree_v());
}

void NurbsSurface::from_v_curves(const vector<NurbsCurve>& vv) //reuse U knots and degree
{
	if (vv.empty())
		return;

	//update knots
	set_knots_v(vv[0].knots());

	//update_points
	int nbPointsV = vv[0].nb_points();
	vector<Point3> vp(nb_points_u() * nbPointsV);
	vector<double> vw(nb_points_u() * nbPointsV);
	for (int u = 0; u < nb_points_u(); u++)
	{
		const NurbsCurve& nv = vv[u];

		for (int v = 0; v < nbPointsV; v++)
		{
			vp[u + v * nb_points_u()] = nv.points()[v];
			vw[u + v * nb_points_u()] = nv.weights()[v];
		}
	}
	set_points(vp, nb_points_u(), vv[0].nb_points());
	set_weights(vw);
	set_degree(degree_u(), vv[0].degree());
}

void NurbsSurface::evaluate(double u, double v, Point3& p) const
{
	//todo optimize all:
	assert(_points.size() == _weights.size());

	int knotIndexU = find_knot_span(_knotsU, u);
	int knotIndexV = find_knot_span(_knotsV, v);
	int iNbCtrlPointsU = nb_points_u();
	int iNbCtrlPointsV = nb_points_v();

	assert(iNbCtrlPointsU == _knotsU.size() - _degreeU - 1);
	assert(iNbCtrlPointsV == _knotsV.size() - _degreeV - 1);
	assert(iNbCtrlPointsU * iNbCtrlPointsV == _points.size());

	//tensor product
	for (int vi = 0; vi < _degreeV + 1; vi++)
	{
		int idxV = vi + knotIndexV - _degreeV;
		assert(idxV >= 0);
		assert(idxV < iNbCtrlPointsV);

		// evaluate on u direction
		for (int ui = 0; ui < _degreeU + 1; ui++)
		{
			int idxU = ui + knotIndexU - _degreeU;
			assert(idxU >= 0);
			assert(idxU < iNbCtrlPointsU);

			double w = _weights[idxU + iNbCtrlPointsU * idxV];
			_tempWeightsU[ui] = w;
			_tempPointsU[ui] = _points[idxU + iNbCtrlPointsU * idxV] * w;
		}

		for (int ru = 1; ru < _degreeU + 1; ru++)
			for (int ju = _degreeU; ju > ru - 1; ju--)
			{
				double alpha = (u - _knotsU[ju + knotIndexU - _degreeU]) / (_knotsU[ju + 1 + knotIndexU - ru] - _knotsU[ju + knotIndexU - _degreeU]);
				_tempPointsU[ju] = _tempPointsU[ju - 1] * (1. - alpha) + _tempPointsU[ju] * alpha;
				_tempWeightsU[ju] = _tempWeightsU[ju - 1] * (1. - alpha) + _tempWeightsU[ju] * alpha;
			}

		_tempPointsV[vi] = _tempPointsU[_degreeU];
		_tempWeightsV[vi] = _tempWeightsU[_degreeU];
	}

	//evaluate on v direction
	for (int rv = 1; rv < _degreeV + 1; rv++)
		for (int jv = _degreeV; jv > rv - 1; jv--)
		{
			double alpha = (v - _knotsV[jv + knotIndexV - _degreeV]) / (_knotsV[jv + 1 + knotIndexV - rv] - _knotsV[jv + knotIndexV - _degreeV]);
			_tempPointsV[jv] = _tempPointsV[jv - 1] * (1. - alpha) + _tempPointsV[jv] * alpha;
			_tempWeightsV[jv] = _tempWeightsV[jv - 1] * (1. - alpha) + _tempWeightsV[jv] * alpha;
		}

	p = _tempPointsV[_degreeV] / _tempWeightsV[_degreeV];
}