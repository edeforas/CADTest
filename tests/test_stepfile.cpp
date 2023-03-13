#include "StepFile.h"

#include <iostream>
using namespace std;
#include "NurbsFactory.h"
#include "NurbsSurface.h"

///////////////////////////////////////////////////////////////////////////
int main()
{
	NurbsSurface ns;
	NurbsFactory::create_torus(50, 20, ns);

	StepWriter sw;
	sw.open("test_torus.step");
	sw.write(ns);

	cout << "Test Finished.";
	return 0;
}
///////////////////////////////////////////////////////////////////////////