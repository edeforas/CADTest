#include "Transform.h"

#include <cmath>

///////////////////////////////////////////////////////////////////////////
Transform::Transform()
{ }

void Transform::apply_all(vector<Point3>& vp) const
{
	for (auto& p : vp)
		apply(p);
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
Rotation::Rotation(double yaw, double pitch, double roll)
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

void Rotation::set_angles(double yaw, double pitch, double roll)
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

void Rotation::apply(Point3& p) const
{
	//yaw rotation , todo optimize 
	double tmp = p.x();
	p.x() = p.x() * _yawCos + p.z() * _yawSin;
	p.z() = p.z() * _yawCos - tmp * _yawSin;

	//pitch rotation
	tmp = p.y();
	p.y() = p.z() * _pitchSin - p.y() * _pitchCos;
	p.z() = p.z() * _pitchCos + tmp * _pitchSin;

	//roll rotation
	tmp = p.x();
	p.x() = p.x() * _rollCos + p.y() * _rollSin;
	p.y() = p.y() * _rollCos - tmp * _rollSin;
}
///////////////////////////////////////////////////////////////////////////
Scale::Scale(double scaleX, double scaleY, double scaleZ)
{
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;
}

void Scale::apply(Point3& p) const
{
	p.x() *= _scaleX;
	p.y() *= _scaleY;
	p.z() *= _scaleZ;
}
///////////////////////////////////////////////////////////////////////////