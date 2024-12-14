#include "NurbsCurve.h"
#include "NurbsUtil.h"
#include "NurbsFactory.h"

#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

void test(bool b, string s="")
{
	if (b == false)
	{
		cout << "condition: [" << s << "] is not realized!" << endl;
		exit(-1);
	}
}

void test_near(double a, double ref, double epsilon=1.e-10,const string& sMessage="")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}

void test_knots()
{
	NurbsCurve n;
	vector<double> knots = { 0,0,1,1 };

	int i_0= n.find_knot_span(knots,0.);
	test_near(i_0, 1);

	int i_05 = n.find_knot_span(knots, 0.5);
	test_near(i_05, 1);

	int i_1 = n.find_knot_span(knots, 1.);
	test_near(i_1, 1);

	//extrapolation
	int i_m01 = n.find_knot_span(knots, -0.1);
	test_near(i_m01, 1);

	int i_11 = n.find_knot_span(knots, 1.1);
	test_near(i_11, 1);
}


void test_simple_segment()
{
	cout << endl << "Test simple segment" << endl;

	NurbsCurve n;
	int degree = 1;
	vector<double> knots = { 0,0,1,1 };
	vector<double> weights(2,1.);
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

void test_half_circle_deg3()
{
	cout << endl << "Test Quarter Circle" << endl;

	NurbsCurve n;
	int degree = 3;
	vector<double> knots = { 0,0,0,0,1,1,1,1 };
	vector<double> weights = { 1.,1./3.,1./3.,1. };
	vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,2.,0.),Point3(-1.,2.,0.),Point3(-1.,0.,0.) };

	n.set_degree(degree);
	n.set_knots(knots);
	n.set_weights(weights);
	n.set_points(points);

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
		double norm = p.norm();
		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
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
	vector<double> weights(4,1.);
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
//		cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		test_near(norm, 1., 1.e-10);
	}
}

void test_random_deg2()
{
	cout << endl << "Test Random Deg2" << endl;

	NurbsCurve n;
	int degree = 2;
	vector<Point3> points;
	int nbPoints = 20;

	for (int i = 0; i < nbPoints; i++)
		points.push_back( Point3((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX) );

	NurbsFactory::create_curve_from_points(points, degree,n);

	for (double u = 0.; u <= 1.; u += 0.01)
	{
		Point3 p;
		n.evaluate(u, p);
	//	cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << endl;
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
	test_near(n.knots().size() , 7);
	for (double u = 0.; u <= 1.; u += 0.01)
	{
		//Point3 p;
		//n.evaluate(u, p);
		//double norm = p.norm();
		//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
		//test_near(norm, 1., 1.e-10); //TODO
	}
}
///////////////////////////////////////////////////////////////////////////
void test_is_closed()
{
	cout << endl << "test_is_closed" << endl;

	{
		NurbsCurve n;
		test(n.is_closed() == false);
	}

	{
		NurbsCurve n;
		vector<Point3> points = { Point3(1.,0.,0.) };
		NurbsFactory::create_curve_from_points(points, 1, n);
		test(n.is_closed() == false);
	}

	{
		NurbsCurve n;
		vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(0.,1.,0.) };
		NurbsFactory::create_curve_from_points(points, 1, n);
		test(n.is_closed() == false);
	}

	{
		NurbsCurve n;
		vector<Point3> points = { Point3(1.,0.,0.),Point3(1.,1.,0.),Point3(1.,0.,0.) };
		NurbsFactory::create_curve_from_points(points, 1, n);
		test(n.is_closed() == true);
	}

	{
		NurbsCurve n;
		vector<Point3> points = { Point3(1.+1.1e-6,0.,0.),Point3(1.,1.,0.),Point3(1.,0.,0.) };
		NurbsFactory::create_curve_from_points(points, 1, n);
		test(n.is_closed() == false);
	}
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_knots();
	test_simple_segment();
	test_quarter_circle();
	test_half_circle_deg3();
	test_full_circle();
	test_cubic_circle_approximation();
	
	test_random_deg2();
	test_is_closed();

	//test_knot_insertion();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////