#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsFactory.h"
#include "NurbsSolid.h"
#include "NurbsExtrude.h"
#include "NurbsUtil.h"
#include "OBJFile.h"

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
void test_nurbssolid_create_cylinder()
{
	cout << endl << "test_nurbssolid_create_cylinder" << endl;

	NurbsSolid ns;
	NurbsFactory::create_cylinder(1, 3, ns);

	Mesh m;
	NurbsUtil::to_mesh(ns, m, 10);
	OBJFile::save("test_nurbssolid_create_cylinder.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbssolid_create_sphere()
{
	cout << endl << "test_nurbssolid_create_sphere" << endl;

	NurbsSolid ns;
	NurbsFactory::create_sphere(2, ns);

	Mesh m;
	NurbsUtil::to_mesh(ns, m, 10);
	OBJFile::save("test_nurbssolid_create_sphere.obj", m);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbssolid_create_torus()
{
	cout << endl << "test_nurbssolid_create_torus" << endl;

	NurbsSolid ns;
	NurbsFactory::create_torus(5,2, ns);

	Mesh m;
	NurbsUtil::to_mesh(ns, m, 10);
	OBJFile::save("test_nurbssolid_create_torus.obj", m);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_nurbs_factory_create_circle();
	test_nurbs_factory_create_sphere();
	test_nurbssolid_create_cylinder();
	test_nurbssolid_create_sphere();
	test_nurbssolid_create_torus();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////