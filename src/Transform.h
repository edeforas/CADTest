#ifndef _Transform_
#define _Transform_

#include "Geometry.h"

class Transform
{
public:
	Transform();

	virtual void apply(Point3& p) const =0 ;
};

class Translation : public Transform
{
public:
	Translation(const Point3& translation);

	virtual void apply(Point3& p) const override;

private:
	Point3 _translation;
};

class Rotation : public Transform
{
public:
	Rotation(double yaw, double pitch, double roll);

	virtual void apply(Point3& p) const override;

private:
	double 	_yaw, _pitch, _roll;
	double _yawCos, _yawSin, _pitchCos, _pitchSin, _rollCos, _rollSin;
};

///////////////////////////////////////////////////////////////////////////

class Scale : public Transform
{
public:
	Scale(double scaleX, double scaleY, double scaleZ);

	virtual void apply(Point3& p) const override;

private:
	double 	_scaleX, _scaleY, _scaleZ;
};

///////////////////////////////////////////////////////////////////////////
#endif