#ifndef _RendererCamera_
#define _RendererCamera_

//very old code

#include "Geometry.h"
#include "Transform.h"

class RendererCamera
{
public:
	RendererCamera();
	void set_angles(double yaw, double pitch, double roll);
	void set_origin(double x, double y, double z, double ahead);
	void set_screen(int width, int height, double zoom);
	Point3 local_ref(const Point3& pc) const;
	void project(const Point3& pPixels, int& screenx, int& screeny, double& w); //w =1/z

private:
	//camera position
	double _x, _y, _z, _ahead;

	// screen properties
	double _zoomFactor;
	int _screenCenterX, _screenCenterY;

	RotationEulerAngles _rot;
};

#endif
