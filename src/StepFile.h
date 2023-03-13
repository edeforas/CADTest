#ifndef _StepFile_
#define _StepFile_

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class NurbsSurface;
class NurbsSolid;
class Point3;

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

	void write(const NurbsSurface& n);
	void write(const NurbsSolid& n);

private:
	void write_header();
	void write_footer();
	void write_cartesian_point(const Point3& p);

	ofstream _f;
	string _sNameFile;
	int _iItemIndent;
};

#endif