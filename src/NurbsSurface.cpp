#include "NurbsSurface.h"
#include "Mesh.h"

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

int NurbsSurface::find_knot_span(const vector <double>& knots,double t) const
{
	//dichotomy
	int iMin = 0;
	int iMax = knots.size();

	while (iMin + 1 < iMax)
	{
		int iMeanIndex = (iMin + iMax) / 2;

		if (t >= knots[iMeanIndex])
			iMin = iMeanIndex;
		else
			iMax = iMeanIndex;
	}

	assert(iMin >= 0);
	assert(iMin < knots.size());
	assert(t >= knots[iMin]);
	assert(t < knots[iMin + 1]);
	assert(knots[iMin] < knots[iMin + 1]);

	return iMin;
}

//todo optimize all:
void NurbsSurface::evaluate(double u, double v, Point3& p) const
{
	assert(_points.size() == _weights.size());

	int knotIndexU = find_knot_span(_knotsU,u);
	int knotIndexV = find_knot_span(_knotsV,v);


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

void NurbsSurface::to_mesh(Mesh& m) const
{
	m.clear();
	if (_points.empty())
		return;

	double deltaU = 1. / (_points.size() * 10.); //todo set 10 dynamic
	double deltaV = 1. / (_points.size() * 10.); //todo set 10 dynamic
	Point3 p;
	for (double u = 0; u <= 1.; u += deltaU) // todo last point?
		for (double v = 0; v <= 1.; v += deltaV) // todo last point?
		{
			evaluate(u,v, p);
		//polyline.push_back(p);
		}
}

///////////////////////////////////////////////////////////////////////////