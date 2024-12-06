#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsFactory.h"
#include "NurbsExtrude.h"
#include "NurbsUtil.h"
#include "Solid.h"
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
void test_solid_cylinder()
{
	Solid s;
	
	cout << endl << "test_nurbsextrude_cylinder" << endl;

	//create profile curve
	NurbsCurve nc;
	NurbsFactory::create_circle(1., nc);

	Point3 direction(0, 0, 3);
	NurbsSurface ns;

	// extrude
	NurbsExtrude ne;
	ne.extrude(nc, direction, ns);

	s.add_surface(ns);
	
	Mesh m;
	NurbsUtil::to_mesh(ns,m,10);
	OBJFile::save("test_solid_cylinder.obj", m);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_solid_cylinder();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////