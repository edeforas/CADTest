#include "NurbsSurface.h"

#include <cassert>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////
NurbsSurface::NurbsSurface() :
	_degreeU(0), _degreeV(0)
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
}

void NurbsSurface::set_degree(int degreeU,int degreeV) //same degre for u and v
{
	_degreeU = degreeU;
	_degreeV = degreeV;

	//_tempPoints.resize((degree + 1)* (degree + 1));
	//_tempWeights.resize((degree + 1) * (degree + 1));
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

void NurbsSurface::set_weights(const vector <double>& weights)
{
	_weights = weights;
}

void NurbsSurface::set_points(const vector <Point3>& points)
{
	_points = points;
}

int NurbsSurface::find_knot_span_u(double u)
{
	//not optimized for now , later: dichomoty
	for (int i = 0; i < _knotsU.size() - 1; i++)
	{
		if ((u >= _knotsU[i]) && (u <= _knotsU[i + 1]) && (_knotsU[i] < _knotsU[i + 1]))
			break;
	}
	return -1; //bad
}

int NurbsSurface::find_knot_span_v(double v)
{
	//not optimized for now , later: dichomoty
	for (int i = 0; i < _knotsV.size() - 1; i++)
	{
		if ((v >= _knotsV[i]) && (v <= _knotsV[i + 1]) && (_knotsV[i] < _knotsV[i + 1]))
			break;
	}
	return -1; //bad
}

//todo optimize all:
void NurbsSurface::evaluate(double u, double v, Point3& p)
{
	assert(_points.size() == _weights.size());

	int knotIndexU = find_knot_span_u(u);
	int knotIndexV = find_knot_span_v(v);
	assert(knotIndexU >= 0);
	assert(knotIndexU < _knotsU.size());
	assert(knotIndexV >= 0);
	assert(knotIndexV < _knotsV.size());
	//int iPointStride = _degreeU + 1;
	/*
	for (int j = 0; j < _degree + 1; j++)
	{
		int idx = j + knotIndex - _degree;

		//todo check if necessary:
		if (idx > _points.size() - 1)
			idx = _points.size() - 1;

		double w = _weights[idx];

		_tempWeights[j] = w;
		_tempPoints[j] = _points[idx] * w;
	}

	for (int r = 1; r < _degree + 1; r++)
		for (int j = _degree; j > r - 1; j--)
		{
			double alpha = (t - _knots[j + knotIndex - _degree]) / (_knots[j + 1 + knotIndex - r] - _knots[j + knotIndex - _degree]);
			_tempPoints[j] = _tempPoints[j - 1] * (1. - alpha) + _tempPoints[j] * alpha;
			_tempWeights[j] = _tempWeights[j - 1] * (1. - alpha) + _tempWeights[j] * alpha;
		}

	p = _tempPoints[_degree] / _tempWeights[_degree];
*/
}

///////////////////////////////////////////////////////////////////////////