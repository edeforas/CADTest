#ifndef _StepFile_
#define _StepFile_

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class NurbsSurface;

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

private:
	void write_header();
	void write_footer();

	ofstream _f;
	string _sNameFile;
};

#endif