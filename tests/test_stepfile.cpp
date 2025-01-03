#include "StepFile.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
int main()
{
//	Body body;
//	StepFile::load("test_sphere_hole.step", body);
//	StepFile::save("test_sphere_hole_out.step", body);

	StepWriter sw;
	sw.open("test_sphere_hole_out.step");
	sw.close();

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////