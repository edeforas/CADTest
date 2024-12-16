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
	void set_angles(double yaw, double pitch, double roll);

	void reset();

	virtual void apply(Point3& p) const =0 ;

private:
	Point3 _translation;
	double 	_yaw , _pitch, _roll;
	double _yawCos, _yawSin, _pitchCos, _pitchSin, _rollCos, _rollSin;
};

class Translation : public Transform
{
public:
	Translation(const Point3& translation);

	virtual void apply(Point3& p) const;

private:
	Point3 _translation;
};

///////////////////////////////////////////////////////////////////////////
#endif