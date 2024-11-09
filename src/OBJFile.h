#ifndef _OBJFile_
#define _OBJFile_

#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "Mesh.h"

class OBJWriter
{
public:
	OBJWriter();
	virtual ~OBJWriter();

	void open(const string& filename);
	bool is_open();
	void close();

	void write(const Mesh& to_mesh);
	void write(const vector<Point3>& polyline);
private:
	ofstream _f;
	int _verticesCount;
};

namespace OBJFile
{
	bool save(const string& filename, const Mesh& to_mesh);
	bool load(const string& filename, Mesh& to_mesh);
}


#endif