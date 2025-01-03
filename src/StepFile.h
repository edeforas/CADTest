#ifndef _StepFile_
#define _StepFile_

#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "Mesh.h"

namespace StepFile
{
//	bool save(const string& filename, const Body& body);
//	bool load(const string& filename, Body& body);
}

class StepWriter
{
public:
	StepWriter();
	virtual ~StepWriter();

	void open(const string& filename);
	bool is_open();
	void close();

	void write(const Mesh& to_mesh);
	void write(const vector<Point3>& polyline);

private:
	ofstream _f;
};

#endif