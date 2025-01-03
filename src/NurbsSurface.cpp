#include "NurbsSurface.h"
#include "Mesh.h"

#include <cassert>
#include <algorithm>
using namespace std;

#include "Transform.h"

///////////////////////////////////////////////////////////////////////////
NurbsSurface::NurbsSurface() :
	_degreeU(0), _degreeV(0), _iNbPointsU(0), _iNbPointsV(0)
{ }

NurbsSurface::~NurbsSurface()
{ }

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

void NurbsSurface::set_degree(int degreeU,int degreeV)
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

	//todo use a Matrix class

	//compute min and max
	double dMin = _knotsU[0];
	double dMax = _knotsU[0];
	for (int i = 1; i < _knotsU.size(); i++)
	{
		double v = _knotsU[i];
		dMin = min(dMin, v);
		dMax = max(dMax, v);
	}

	//apply scale so that 0<= knots <= 1
	for (int i = 0; i < _knotsU.size(); i++)
	{
		_knotsU[i] = (_knotsU[i] - dMin) / (dMax - dMin);
	}
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

	//todo use a Matrix class

	//compute min and max
	double dMin = _knotsV[0];
	double dMax = _knotsV[0];
	for (int i = 1; i < _knotsV.size(); i++)
	{
		double v = _knotsV[i];
		dMin = min(dMin, v);
		dMax = max(dMax, v);
	}

	//apply scale so that 0<= knots <= 1
	for (int i = 0; i < _knotsV.size(); i++)
	{
		_knotsV[i] = (_knotsV[i] - dMin) / (dMax - dMin);
	}
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


void NurbsSurface::set_weights(const vector <double>& weights)
{
	_weights = weights;
}

void NurbsSurface::set_equals_weights() //non rational
{
	_weights.resize(_points.size(), 1.);
}

void NurbsSurface::set_points(const vector <Point3>& points,int iNbPointsU,int iNbPointsV)
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

const vector<Point3>& NurbsSurface::points() const
{
	return _points;
}

vector<Point3>& NurbsSurface::points()
{
	return _points;
}

int NurbsSurface::find_knot_span(const vector <double>& knots,double t)
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

//todo optimize all:
void NurbsSurface::evaluate(double u, double v, Point3& p) const
{
	assert( _points.size() == _weights.size());

	int knotIndexU = find_knot_span(_knotsU,u);
	int knotIndexV = find_knot_span(_knotsV,v);
	int iNbCtrlPointsU = nb_points_u();
	int iNbCtrlPointsV = nb_points_v();

	assert(iNbCtrlPointsU == _knotsU.size() - _degreeU - 1);
	assert(iNbCtrlPointsV == _knotsV.size() - _degreeV - 1);
	assert(iNbCtrlPointsU*iNbCtrlPointsV == _points.size());
	
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
	
	p = _tempPointsV[_degreeV]/ _tempWeightsV[_degreeV];
}

void NurbsSurface::apply_transform(const Transform& t)
{
	for (auto& p : points())
		t.apply(p);
}