#ifndef _Transform_
#define _Transform_

#include <vector>
using namespace std;

#include "Geometry.h"

class Transform
{
public:
	Transform();

	void set_global_translation(const Point3& translation);
	void set_global_translation(double x, double y, double z);
	void reset();

	void apply(vector<Point3>& v) const;
	void apply(Point3& p) const;

private:
	Point3 _translation;
};

///////////////////////////////////////////////////////////////////////////
#endif