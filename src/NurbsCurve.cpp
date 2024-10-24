#include "NurbsCurve.h"

#include <cassert>
#include <algorithm>
using namespace std;

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

int NurbsCurve::find_knot_span(const vector <double>& knots,double t) const
{
	//dichotomy
	int iMin = 0;
	int iMax = _knots.size();

	while (iMin+1 < iMax)
	{
		int iMeanIndex = (iMin + iMax)/2;

		if (t >= _knots[iMeanIndex])
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


void NurbsCurve::insert_knot(double u)
{
	//as in https://public.vrac.iastate.edu/~oliver/courses/me625/week9.pdf

	int indexU = find_knot_span(_knots,u);

	vector<double> k=_knots;
	vector<Point3> p;
	vector<double> w;

	//reconstruct the curve
	for (int i = 0; i < _points.size(); i++)
	{
		if( (i <= indexU - _degree) || (i>=indexU+1) )
		{
			p.push_back(_points[i]);
			w.push_back(_weights[i]);
		}
		else
		{
			double dAlpha = (u - _knots[i]) / (_knots[i + _degree] - _knots[i]);

			w.push_back(_weights[i]* dAlpha + _weights[i - 1]* (1. - dAlpha));
			p.push_back(_points[i] * dAlpha + _points[i - 1]* (1. - dAlpha));
		}
	}

	k.insert(k.begin()+indexU+1,u);
	set_knots(k);
	set_weights(w);
	set_points(p);
}

void NurbsCurve::evaluate(double u, Point3& p) const
{
	//todo optimize all:
	assert(_points.size() == _weights.size());

	int knotIndex = find_knot_span(_knots,u);

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
			double alpha = (u - _knots[j + knotIndex - _degree]) / (_knots[j + 1 + knotIndex - r] - _knots[j + knotIndex - _degree]);
			_tempPoints[j] = _tempPoints[j - 1] * (1. - alpha) + _tempPoints[j] * alpha;
			_tempWeights[j] = _tempWeights[j - 1] * (1. - alpha) + _tempWeights[j] * alpha;
		}

	p = _tempPoints[_degree] / _tempWeights[_degree];
}

///////////////////////////////////////////////////////////////////////////
void NurbsCurve::to_polyline(vector<Point3>& polyline) const
{
	polyline.clear();
	if (_points.empty())
		return;

	double deltaT = 1. / (_points.size() * 10.); //todo set 10 dynamic
	Point3 p;
	for (double t = 0; t <= 1.; t += deltaT) // todo last point?
	{
		evaluate(t, p);
		polyline.push_back(p);
	}
}