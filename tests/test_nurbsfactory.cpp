#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsFactory.h"

#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

void test_near(double a, double ref, double epsilon=1.e-10,const string& sMessage="")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}
///////////////////////////////////////////////////////////////////////////
void test_nurbs_factory_create_circle()
{
	cout << endl << "test_nurbs_factory_create_circle" << endl;

	NurbsCurve n;

	for (double dRadius = 0.1; dRadius < 100.; dRadius *= 2.)
	{
		NurbsFactory::create_circle(dRadius, n);

		for (double u = 0.; u <= 1.; u += 0.01)
		{
			Point3 p;
			n.evaluate(u, p);
			double norm = p.norm();
			//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
			test_near(norm, dRadius, 1.e-10);
		}
	}
}
///////////////////////////////////////////////////////////////////////////
void test_nurbs_factory_create_sphere()
{
	cout << endl << "test_nurbs_factory_create_sphere" << endl;

	for (double dRadius = 0.1; dRadius < 100.; dRadius *= 2.)
	{
		NurbsSurface ns;
		NurbsFactory::create_sphere(dRadius, ns);

		for (double u = 0.; u <= 1.; u += 0.01)
			for (double v = 0.; v <= 1.; v += 0.01)
			{
				Point3 p;
				ns.evaluate(u, v, p);
				double norm = p.norm();
				//cout << "u=" << u << " x=" << p.x() << " y=" << p.y() << " z=" << p.z() << " norm=" << norm << endl;
				test_near(norm, dRadius, 1.e-10);
			}
	}
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_nurbs_factory_create_circle();
	test_nurbs_factory_create_sphere();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////