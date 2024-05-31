#include "NurbsCurve.h"

#include <iostream>
#include <cassert>
using namespace std;

void test_near(double a, double ref, double epsilon,const string& sMessage="")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}

void test_simple_segment()
{
	cout << endl << "Test simple segment" << endl;

	NurbsCurve n;
	int degree = 1;
	vector<double> knots = { 0,0,1,1 };
	vector<double> weights = { 1.,1. };
	vector<Point3> points = { Point3(0.,0.,0.),Point3(1.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		test_near(p.x(), u, 1e-10);
		test_near(p.y(), u, 1e-10);
		test_near(p.z(), 0, 1e-10);

		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << endl;
	}
}

void test_quarter_circle()
{
	cout << endl<< "Test Quarter Circle" << endl;

	NurbsCurve n;
	int degree = 2;
	vector<double> knots = { 0,0,0,1,1,1 };
	vector<double> weights = { 1.,1./sqrt(2.),1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		test_near(norm, 1., 1.e-10);
	}
}

void test_cubic_circle_approximation()
{
	//	approximation using cubic NURBS, not rational
	//	from "Good Approximation of Circles by Curvature-Continuous Bézier curves"
	//	0.55 number optimized to 0.5519151 for a lower max error

	cout << endl << "Test Cubic Circle approximation" << endl;

	NurbsCurve n;
	int degree = 3;
	vector<double> knots = { 0,0,0,0,1,1,1,1 };
	vector<double> weights = { 1.,1.,1.,1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,0.5519151,0.), Point3(0.5519151,1.,0.), Point3(0.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		test_near(norm, 1., 2.e-4);
	}
}

void test_full_circle()
{
	cout << endl << "Test Full Circle" << endl;

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

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		test_near(norm, 1., 1.e-10);
	}
}

void test_random_deg2()
{
	cout << endl << "Test Random Deg2" << endl;

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


void test_knot_insertion()
{
	cout << endl << "Test knot insertion" << endl;

	NurbsCurve n;
	int degree = 2;
	vector<double> knots = { 0,0,0,1,1,1 };
	vector<double> weights = { 1.,1. / sqrt(2.),1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		test_near(norm, 1., 1.e-10);
	}

	//now insert a knot a 0.3 and retest
	n.insert_knot(0.3);
	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		test_near(norm, 1., 1.e-10);
	}

}





///////////////////////////////////////////////////////////////////////////
int main()
{
	test_simple_segment();
	test_quarter_circle();
	test_full_circle();
	test_cubic_circle_approximation();

	test_random_deg2();

	test_knot_insertion();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////