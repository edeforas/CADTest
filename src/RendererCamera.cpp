#include <cmath>
using namespace std;

#include "RendererCamera.h"

////////////////////////////////////////////////////////////////////////////////
RendererCamera::RendererCamera()
{
	set_angles(0., 0., 0.);
	set_origin(0., 0., 0., 0.);
	set_screen(0, 0, 0.);
}
////////////////////////////////////////////////////////////////////////////////
void RendererCamera::set_angles(double yaw, double pitch, double roll)
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
////////////////////////////////////////////////////////////////////////////////
void RendererCamera::set_origin(double x, double y, double z, double ahead)
{
	_x = x; _y = y; _z = z;
	_ahead = ahead;
}
////////////////////////////////////////////////////////////////////////////////
void RendererCamera::set_screen(int width, int height, double zoom)
{
	_screenCenterX = width / 2;
	_screenCenterY = height / 2;
	_zoomFactor = zoom;
}
////////////////////////////////////////////////////////////////////////////////
Point3 RendererCamera::local_ref(const Point3& pc) const
{
	Point3 pLocal=pc;

	//origin translation
	pLocal.x() -= _x;
	pLocal.y() -= _y;
	pLocal.z() -= _z;

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

	// ahead move
	pLocal.z() = pLocal.z() + _ahead;

	return pLocal;
}
////////////////////////////////////////////////////////////////////////////////
void RendererCamera::project(const Point3& pPixels, int& screenx, int& screeny, double& w)
{
	Point3 pc = local_ref(pPixels);

	screenx = (int)(pc.x() * _zoomFactor / pc.z() + _screenCenterX+0.5);
	screeny = (int)(pc.y() * _zoomFactor / pc.z() + _screenCenterY+0.5);
	if (pc.z() != 0.)
		w = 1. / pc.z();
	else
		w = 0.;
}
////////////////////////////////////////////////////////////////////////////////
