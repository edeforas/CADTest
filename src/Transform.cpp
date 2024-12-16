#include "Transform.h"

#include <cmath>

///////////////////////////////////////////////////////////////////////////
Transform::Transform()
{
	reset();
}

void Transform::reset()
{
	set_angles(0., 0., 0.);
	set_global_translation( Point3(0., 0., 0.));
}
/*
void Transform::apply(Point3& p) const
{
	p += _translation; //todo rotation
	
/*
	//yaw rotation
	double tmp = pLocal.x();
	pLocal.x() = pLocal.x() * _yawCos + pLocal.z() * _yawSin;
	pLocal.z() = pLocal.z() * _yawCos - tmp * _yawSin;

	//pitch rotation
	tmp = pLocal.y();
	pLocal.y() = pLocal.z() * _pitchSin - pLocal.y() * _pitchCos;
	pLocal.z() = pLocal.z() * _pitchCos + tmp * _pitchSin;

	//roll rotation
	tmp = pLocal.x();
	pLocal.x() = pLocal.x() * _rollCos + pLocal.y() * _rollSin;
	pLocal.y() = pLocal.y() * _rollCos - tmp * _rollSin;
*/

void Transform::set_global_translation(const Point3& translation)
{
	_translation = translation;
}

void Transform::set_global_translation(double x, double y, double z)
{
	_translation = Point3(x, y, z);
}

void Transform::set_angles(double yaw, double pitch, double roll)
{
	double dDegToRad = 2. * 3.14159265359 / 360.;

	_yaw = yaw;
	_pitch = pitch;
	_roll = roll;

	_yawCos = cos(_yaw * dDegToRad);
	_yawSin = sin(_yaw * dDegToRad);
	_pitchCos = cos(_pitch * dDegToRad);
	_pitchSin = sin(_pitch * dDegToRad);
	_rollCos = cos(_roll * dDegToRad);
	_rollSin = sin(_roll * dDegToRad);
}
///////////////////////////////////////////////////////////////////////////
Translation::Translation(const Point3& translation)
{
	_translation = translation;
}

void Translation::apply(Point3& p) const
{
	p += _translation; 
}
///////////////////////////////////////////////////////////////////////////