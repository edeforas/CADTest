#include "NurbsCurve.h"

#include <iostream>
using namespace std;

void test_simple_segment()
{
	NurbsCurve n;
	int degree = 1;
	vector<double> knots = { 0,0,1,1 };
	vector<double> weights = { 1.,1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(0.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.1)
	{
		Point3 p;
		n.evaluate(u, p);

		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << endl;
	}
}

void test_quarter_circle()
{
	NurbsCurve n;
	int degree = 2;
	vector<double> knots = { 0,0,0,1,1,1 };
	vector<double> weights = { 1.,1./sqrt(2.),1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.1)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
	}
}

void test_cubic_circle_approximation()
{
	//	approximation using cubic NURBS, not rational
	//	from "Good Approximation of Circles by Curvature-Continuous Bézier curves"
	//	0.55 number optimized to 0.5519151 for a lower max error

	NurbsCurve n;
	int degree = 3;
	vector<double> knots = { 0,0,0,0,1,1,1,1 };
	vector<double> weights = { 1.,1.,1.,1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,0.5519151,0.), Point3(0.5519151,1.,0.), Point3(0.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.1)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
	}
}

void test_full_circle()
{
	NurbsCurve n;
	int degree = 2;
	vector<double> knots = { 0., 0., 0., 0.25, 0.25, 0.5, 0.5, 0.75, 0.75, 1., 1., 1. };
	vector<double> weights = { 1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1.,1. / sqrt(2.),1. };
	vector<Point3> points = {
		Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.),
		Point3(-1.,1.,0.),Point3(-1.,0.,0.),Point3(-1.,-1.,0.),
		Point3(0.,-1.,0.),Point3(1.,-1.,0.),Point3(1.,0.,0.)
	};

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.1)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
	}
}

void test_random_points()
{
	NurbsCurve n;
	int degree = 2;
	vector<double> knots;
	vector<double> weights;
	vector<Point3> points;
	int nbPoint = 20;

	knots.push_back(0);
	knots.push_back(0);
	for (int i = 0; i < nbPoint; i++)
	{
		points.push_back( Point3((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX) );
		weights.push_back(1.);
		knots.push_back(i);
	}
	knots.push_back(nbPoint);
	knots.push_back(nbPoint);
	knots.push_back(nbPoint);

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.1)
	{
		Point3 p;
		n.evaluate(u, p);
		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << endl;
	}
}

///////////////////////////////////////////////////////////////////////////
int main()
{
	test_simple_segment();
	test_quarter_circle();
	test_full_circle();
	test_cubic_circle_approximation();

	test_random_points();

	return 0;
}
///////////////////////////////////////////////////////////////////////////