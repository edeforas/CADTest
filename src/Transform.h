#ifndef _Transform_
#define _Transform_

#include "Geometry.h"
#include "Mesh.h"

#include <vector>
using namespace std;

class Transform
{
public:
	Transform();

	void set_global_translation(const Point3& translation);
	void set_global_translation(double x, double y, double z);
	void reset();

	void apply(Mesh& m);
	void apply(vector<Point3>& v);

private:
	Point3 _translation;
};

#endif