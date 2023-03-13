#include "NurbsCurve.h"
#include "NurbsSolid.h"
#include "NurbsUtil.h"
#include "StepFile.h"

#include "MeshFactory.h"
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
void test_nurbsutil_create_icosahedron()
{
	Mesh ico,ico_out;
	MeshFactory::create_icosahedron(30.,ico);
	
	NurbsSolid n;
	NurbsUtil::create_from_mesh(ico,n);

	NurbsUtil::to_mesh(n, ico_out, 10);
	OBJFile::save("test_nurbsutil_create_icosahedron_orig.obj", ico);
	OBJFile::save("test_nurbsutil_create_icosahedron_out.obj", ico_out);

	StepWriter sw;
	sw.open("test_nurbsutil_create_icosahedron.step");
	sw.write(n);
}
///////////////////////////////////////////////////////////////////////////
void test_nurbsutil_create_dodecahedron()
{
	Mesh dodec, dodec_out;
	MeshFactory::create_dodecahedron(30., dodec);

	NurbsSolid n;
	NurbsUtil::create_from_mesh(dodec, n);

	NurbsUtil::to_mesh(n, dodec_out, 10);
	OBJFile::save("test_nurbsutil_create_dodecahedron_orig.obj", dodec);
	OBJFile::save("test_nurbsutil_create_dodecahedron_out.obj", dodec_out);

	StepWriter sw;
	sw.open("test_nurbsutil_create_dodecahedron.step");
	sw.write(n);
}
///////////////////////////////////////////////////////////////////////////
int main()
{
	test_nurbsutil_create_icosahedron();
	test_nurbsutil_create_dodecahedron();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////