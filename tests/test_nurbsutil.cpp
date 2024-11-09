#include "NurbsCurve.h"
#include "NurbsUtil.h"

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

void test_create_circle()
{
	cout << endl << "Test NurbsUtil::create_circle" << endl;

	NurbsCurve n;

	for (double dRadius = 0.1; dRadius < 100.; dRadius *= 2.)
	{
		NurbsUtil::create_circle(dRadius, n);

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
int main()
{
	test_create_circle();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////