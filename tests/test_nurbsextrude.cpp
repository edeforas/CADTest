#include "NurbsExtrude.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
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

void test_extrude_cylinder()
{
	cout << endl << "test_extrude_cylinder" << endl;

	//create profile curve
	NurbsCurve nc;
	NurbsUtil::create_circle(1., nc);

	Point3 direction(0, 0, 1);
	NurbsSurface ns;

	// extrude
	NurbsExtrude ne;
	ne.extrude(nc, direction, ns);

	Mesh m;
	ns.to_mesh(m);
	OBJFile::save("test_extrude_cylinder.obj", m);
}

///////////////////////////////////////////////////////////////////////////

void test_extrude_random_deg2()
{
	cout << endl << "test_extrude_random_deg2" << endl;

	NurbsCurve nc;
	int degree = 2;
	vector<Point3> points;
	int nbPoints = 6;

	for (int i = 0; i < nbPoints; i++)
		points.push_back(Point3((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX));

	nc.create_from_points(points, degree);

	Point3 direction(0, 0, 1.);
	NurbsSurface ns;

	// extrude
	NurbsExtrude ne;
	ne.extrude(nc, direction, ns);

	Mesh m;
	ns.to_mesh(m);
	OBJFile::save("test_extrude_random_deg2.obj", m); //todo debug: bad U shape
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_extrude_cylinder();
	test_extrude_random_deg2();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////