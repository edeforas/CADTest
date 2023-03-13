#include <cmath>
using namespace std;

#include "RendererCamera.h"

////////////////////////////////////////////////////////////////////////////////
RendererCamera::RendererCamera() :
	_rot()
{
	set_angles(0., 0., 0.);
	set_origin(0., 0., 0., 0.);
	set_screen(0, 0, 0.);
}
////////////////////////////////////////////////////////////////////////////////
void RendererCamera::set_angles(double yaw, double pitch, double roll)
{
	_rot.set_angles(yaw, pitch, roll);
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
	Point3 pLocal = pc;

	//origin translation
	pLocal.x() -= _x;
	pLocal.y() -= _y;
	pLocal.z() -= _z;

	_rot.apply(pLocal);

	// ahead move
	pLocal.z() = pLocal.z() + _ahead;

	return pLocal;
}
////////////////////////////////////////////////////////////////////////////////
void RendererCamera::project(const Point3& pPixels, int& screenx, int& screeny, double& w)
{
	Point3 pc = local_ref(pPixels);

	screenx = (int)(pc.x() * _zoomFactor / pc.z() + _screenCenterX + 0.5);
	screeny = (int)(pc.y() * _zoomFactor / pc.z() + _screenCenterY + 0.5);
	if (pc.z() != 0.)
		w = 1. / pc.z();
	else
		w = 0.;
}
////////////////////////////////////////////////////////////////////////////////
