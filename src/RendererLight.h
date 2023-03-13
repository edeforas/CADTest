#ifndef _RendererLight_
#define _RendererLight_

#include "Geometry.h"

class RendererLight
{
public:
	RendererLight();

	virtual void apply(double& dRed, double& dGreen, double& dBlue, const Point3& normal) = 0;
};

class RendererLightAmbiant : public RendererLight
{
public:
	RendererLightAmbiant(int iAmbiantColor = 0x808080, double dAmbiantFactor = 1.);

	virtual void apply(double& dRed, double& dGreen, double& dBlue, const Point3& normal) override;

private:
	double _dAmbiantRed, _dAmbiantGreen, _dAmbiantBlue;
};

class RendererLightDiffuse : public RendererLight
{
public:
	RendererLightDiffuse(int iDiffuseColor = 0xC0C0C0, double dDiffuseFactor = 1., const Point3& direction = Point3(0., 0., 1.));

	virtual void apply(double& dRed, double& dGreen, double& dBlue, const Point3& normal) override;

private:
	double _dDiffuseRed, _dDiffuseGreen, _dDiffuseBlue;
	Point3 _direction;
};

#endif
