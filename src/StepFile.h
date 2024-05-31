#ifndef _STLFile_
#define _STLFile_

#include <string>
using namespace std;

#include "Body.h"

namespace StepFile
{
	bool save(const string& filename, const Body& body);
	bool load(const string& filename, Body& body);
}

#endif