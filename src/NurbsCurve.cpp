#include "NurbsCurve.h"

#include <cassert>

///////////////////////////////////////////////////////////////////////////
NurbsCurve::NurbsCurve() :
	_degree(0)
{ }

NurbsCurve::~NurbsCurve()
{ }

void NurbsCurve::clear()
{
	_degree = 0;
	_knots.clear();
	_weights.clear();
	_points.clear();
}

void NurbsCurve::set_degree(int degree)
{
	_degree = degree;
	_tempPoints.resize(degree + 1);
	_tempWeights.resize(degree + 1);
}

void NurbsCurve::set_knots(const vector <double>& knots)
{
	_knots = knots;

	//todo use a Matrix class

	//compute min and max
	double dMin = _knots[0];
	double dMax = _knots[0];
	for (int i = 1; i < _knots.size(); i++)
	{
		double v = _knots[i];
		dMin = min(dMin, v);
		dMax = max(dMax, v);
	}

	//apply scale so that 0<= knots <= 1
	for (int i = 0; i < _knots.size(); i++)
	{
		_knots[i] = (_knots[i] - dMin) / (dMax - dMin);
	}
}

void NurbsCurve::set_weights(const vector <double>& weights)
{
	_weights = weights;
}

void NurbsCurve::set_points(const vector <Point3>& points)
{
	_points = points;
}

const vector<Point3>& NurbsCurve::points() const
{
	return _points;
}

int NurbsCurve::find_knot_span(double t) const
{
	//not optimized for now , later: dichomoty
	for (int i = 0; i < _knots.size() - 1; i++)
	{
		if ((t >= _knots[i]) && (t <= _knots[i + 1]) && (_knots[i] < _knots[i + 1]))
			return i;
	}
	return -1; //bad
}

//todo optimize all:
void NurbsCurve::evaluate(double t, Point3& p) const
{
	assert(_points.size() == _weights.size());

	int knotIndex = find_knot_span(t);
	assert(knotIndex >= 0);
	assert(knotIndex < _knots.size());

	for (int j = 0; j < _degree+1; j++)
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
}

///////////////////////////////////////////////////////////////////////////