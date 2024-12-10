#include "NurbsCurve.h"
#include "NurbsSurface.h"
#include "NurbsFactory.h"
#include "NurbsExtrude.h"
#include "NurbsUtil.h"
#include "NurbsSolid.h"
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
int main()
{
	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////