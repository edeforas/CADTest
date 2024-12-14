#include "NurbsCurve.h"

#include <cassert>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////
NurbsCurve::NurbsCurve() :
	_degree(0), _iNbPoints(0)
{ }

NurbsCurve::~NurbsCurve()
{ }

void NurbsCurve::clear()
{
	_degree = 0;
	_knots.clear();
	_weights.clear();
	_points.clear();
	_iNbPoints=0;
}

void NurbsCurve::set_degree(int degree)
{
	_degree = degree;
	_tempPoints.resize(degree + 1);
	_tempWeights.resize(degree + 1);
}

int NurbsCurve::degree() const
{
	return _degree;
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

void NurbsCurve::set_uniform()
{
	vector <double> knots;

	for (int i = 0; i <= _degree; i++)
		knots.push_back(0.);

	for (int i = 1; i < _iNbPoints - _degree; i++)
		knots.push_back(i);

	for (int i = 0; i <= _degree; i++)
		knots.push_back(_iNbPoints - _degree);

	set_knots(knots);
}

const vector<double>& NurbsCurve::knots() const
{
	return _knots;
}

void NurbsCurve::set_weights(const vector <double>& weights)
{
	_weights = weights;
}

const vector<double>& NurbsCurve::weights() const
{
	return _weights;
}

void NurbsCurve::set_equals_weights() //non rational
{
	_weights.resize(_iNbPoints, 1.);
}

void NurbsCurve::set_points(const vector <Point3>& points)
{
	_points = points;
	_iNbPoints = _points.size();
}

int NurbsCurve::nb_points() const
{
	return _points.size();
}

const vector<Point3>& NurbsCurve::points() const
{
	return _points;
}

vector<Point3>& NurbsCurve::points()
{
	return _points;
}

bool NurbsCurve::is_closed(double dTol) const
{
	if (_points.size() <= 1)
		return false;
	return (_points[0] - _points[_points.size() - 1]).norm_square() < (dTol * dTol);
}

int NurbsCurve::find_knot_span(const vector <double>& knots,double t)
{
	if (knots.size()<2)
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

	/*
	//dichotomy
	int a = 0;
	int c = knots.size()-1;

	if (t < 0.)
		t = 0.;

	if (t > 1.)
		t = 1.;

	while (c-a > 1)
	{
		assert(a < c);

		int b = (a + c)/2;

		if (t >= knots[b])
			a = b;
		else
			c = b;

		assert(a >= 0);
		assert(a < knots.size());
		assert(c >= 0);
		assert(c < knots.size());

		assert(t >= knots[a]);
		assert(t <= knots[c]);
		assert(knots[a] < knots[c]);
	}

	assert(knots[a] < knots[a + 1]);
	assert(t < knots[a+1]);

	return a;
	*/
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
	assert(_iNbPoints == _weights.size());
	assert(_iNbPoints == _knots.size() - _degree - 1);

	int knotIndex = find_knot_span(_knots,u);

	for (int j = 0; j < _degree+1; j++)
	{
		int idx = j + knotIndex - _degree;
		assert(idx >=0);
		assert(idx < _iNbPoints);

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
///////////////////////////////////////////////////////////////////////////
