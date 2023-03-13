#include "NurbsCurve.h"

#include <cassert>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////
NurbsCurve::NurbsCurve() :
	_degree(0), _iNbPoints(0)
{
}

NurbsCurve::~NurbsCurve()
{
}

void NurbsCurve::clear()
{
	_degree = 0;
	_knots.clear();
	_weights.clear();
	_points.clear();
	_iNbPoints = 0;
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
	scale_knots(_knots);
}

void NurbsCurve::scale_knots(vector<double>& knots)
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
	_weights.assign(_iNbPoints, 1.);
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

int NurbsCurve::find_knot_span(const vector <double>& knots, double t)
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
	// no test for multiplicity for now
	int indexU = find_knot_span(_knots, u);

	vector<double> k = _knots;
	vector<Point3> p;
	vector<double> w;

	//reconstruct the curve
	for (int i = 0; i < _points.size() + 1; i++)
	{
		if (i <= indexU - _degree)
		{
			p.push_back(_points[i] * _weights[i]);
			w.push_back(_weights[i]);
			continue;
		}

		if (i >= indexU + 1)
		{
			p.push_back(_points[i - 1] * _weights[i - 1]);
			w.push_back(_weights[i - 1]);
			continue;
		}

		double dAlpha = (u - _knots[i]) / (_knots[i + _degree] - _knots[i]);
		p.push_back(_points[i] * _weights[i] * dAlpha + _points[i - 1] * _weights[i - 1] * (1. - dAlpha));
		w.push_back(_weights[i] * dAlpha + _weights[i - 1] * (1. - dAlpha));
	}

	//Homogenous to 3D coords
	for (int i = 0; i < p.size(); i++)
		p[i] /= w[i];

	k.insert(k.begin() + indexU + 1, u);
	set_knots(k);
	set_weights(w);
	set_points(p);
}

void NurbsCurve::evaluate(double u, Point3& p) const
{
	//todo optimize all:
	assert(_iNbPoints == _weights.size());
	assert(_iNbPoints == _knots.size() - _degree - 1); //todo, always true ?

	int knotIndex = find_knot_span(_knots, u);

	for (int j = 0; j < _degree + 1; j++)
	{
		int idx = j + knotIndex - _degree;
		assert(idx >= 0);
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
bool NurbsCurve::degree_elevation()
{
	if (_degree >= 3)
		return false; //only deg <=3 are handled

	// from paper: DIRECT DEGREE ELEVATION OF NURBS CURVES Kestutis Jankauskas, Dalius Rubliauskas

	//Procedure ElevateKnots
	vector<double> elevatedKnots, knotMultiplicity;
	int nbKnots = _knots.size();
	int l = 1;
	for (int k = 0; k < nbKnots - 1; k++)
	{
		elevatedKnots.push_back(_knots[k]);

		if (_knots[k] != _knots[k + 1])
		{
			elevatedKnots.push_back(_knots[k]);
			knotMultiplicity.push_back(l);
			l = 0;
		}
		l++;
	}
	knotMultiplicity.push_back(l);
	elevatedKnots.push_back(_knots[nbKnots - 1]);
	elevatedKnots.push_back(_knots[nbKnots - 1]);

	vector<Point3> newPoints;// (2 * _iNbPoints - 1);
	vector<double> newWeights;// (2 * _iNbPoints - 1);

	if (_degree == 1)
	{
		for (int i = 0; i <= _iNbPoints - 2; i++)
		{
			newPoints.push_back(_points[i] * _weights[i]);
			newWeights.push_back(_weights[i]);

			newPoints.push_back((_points[i] * _weights[i] + _points[i + 1] * _weights[i + 1]) / 2.);
			newWeights.push_back((_weights[i] + _weights[i + 1]) / 2.);
		}
		newPoints.push_back(_points[_iNbPoints - 1] * _weights[_iNbPoints - 1]);
		newWeights.push_back(_weights[_iNbPoints - 1]);
	}
	else if (_degree == 2)
	{
		//Procedure DDEQuadratic
		// in: U[m] – knot vector ==_knots
		// in: P[n] – control points ==_points
		// in: S[ns] – knot multiplicity vector ==knotMultiplicity
		// out: Q[n+ns-1] – elevated control points ==newPoints

		int k = 2;
		double b1 = 1. / 3.;
		double b2 = 2. / 3.;

		newPoints.push_back(_points[0] * _weights[0]);
		newWeights.push_back(_weights[0]);

		for (int l = 1; l < knotMultiplicity.size(); l++) // was //for (int l = 1 ; l<= nl – 1 ; l++)
		{
			if (knotMultiplicity[l - 1] > 1)
			{
				newPoints.push_back(_points[k - 1] * _weights[k - 1] * b2 + _points[k - 2] * _weights[k - 2] * b1);
				newWeights.push_back(_weights[k - 1] * b2 + _weights[k - 2] * b1);
			}
			if (knotMultiplicity[l] > 1)
			{
				newPoints.push_back(_points[k] * _weights[k] * b1 + _points[k - 1] * _weights[k - 1] * b2);
				newWeights.push_back(_weights[k] * b1 + _weights[k - 1] * b2);

				newPoints.push_back(_points[k] * _weights[k]);
				newWeights.push_back(_weights[k]);
			}
			else
			{
				double B = (_knots[k + 1] - _knots[k]) / (3 * (_knots[k + 2] - _knots[k]));

				newPoints.push_back(_points[k] * _weights[k] * B + _points[k - 1] * _weights[k - 1] * (1 - B));
				newWeights.push_back(_weights[k] * B + _weights[k - 1] * (1 - B));

				newPoints.push_back(_points[k] * _weights[k] * (B + b2) + _points[k - 1] * _weights[k - 1] * (b1 - B));
				newWeights.push_back(_weights[k] * (B + b2) + _weights[k - 1] * (b1 - B));
			}
			k += knotMultiplicity[l];
		}

		//	newPoints[2 * _iNbPoints - 2] = _points[_iNbPoints - 1] * _weights[_iNbPoints - 1];
		//	newWeights[2 * _iNbPoints - 2] = _weights[_iNbPoints - 1];
	}

	//homogenous to 3d points
	for (int i = 0; i < newPoints.size(); i++)
		newPoints[i] /= newWeights[i];

	set_knots(elevatedKnots);
	set_points(newPoints);
	set_weights(newWeights);
	set_degree(_degree + 1);
	return true;
}
///////////////////////////////////////////////////////////////////////////