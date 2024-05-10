#include "NurbsRuled.h"

#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsUtil.h"
#include "NurbsFactory.h"
#include "Transform.h"

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
void test_nurbsruled_cylinder()
{
	cout << endl << "test_nurbsruled_cylinder" << endl;

	//create profile curve
	NurbsCurve nc1,nc2;
	NurbsFactory::create_circle(1., nc1);
	NurbsFactory::create_circle(1., nc2);

	// translate nc2
	nc2.apply_transform(Translation(Point3(0, 0, 1)));

	NurbsSurface ns;

	// ruled
	NurbsRuled ne;
	ne.create_ruled(nc1,nc2, ns);

	Mesh m;
	NurbsUtil::to_mesh(ns,m,10);
	OBJFile::save("test_nurbsruled_cylinder.obj", m);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_nurbsruled_cylinder();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////