#include <cmath>
using namespace std;

#include "RendererLight.h"

RendererLight::RendererLight()
{
}

////////////////////////////////////////////////////////////////////////////////
RendererLightAmbiant::RendererLightAmbiant(int iAmbiantColor, double dAmbiantFactor)
{
	_dAmbiantRed = dAmbiantFactor * ((iAmbiantColor >> 16) & 0xff) / 256.;
	_dAmbiantGreen = dAmbiantFactor * ((iAmbiantColor >> 8) & 0xff) / 256.;
	_dAmbiantBlue = dAmbiantFactor * ((iAmbiantColor) & 0xff) / 256.;
}

void RendererLightAmbiant::apply(double& dRed, double& dGreen, double& dBlue, const Point3& normal)
{
	dRed *= _dAmbiantRed;
	dGreen *= _dAmbiantGreen;
	dBlue *= _dAmbiantBlue;
}
////////////////////////////////////////////////////////////////////////////////
RendererLightDiffuse::RendererLightDiffuse(int iDiffuseColor, double dDiffuseFactor, const Point3& direction) :
	_direction(direction)
{
	_dDiffuseRed = dDiffuseFactor * ((iDiffuseColor >> 16) & 0xff) / 256.;
	_dDiffuseGreen = dDiffuseFactor * ((iDiffuseColor >> 8) & 0xff) / 256.;
	_dDiffuseBlue = dDiffuseFactor * ((iDiffuseColor) & 0xff) / 256.;
}

void RendererLightDiffuse::apply(double& dRed, double& dGreen, double& dBlue, const Point3& normal)
{
	double proj = normal.dot_product(_direction);
	if (proj < 0.)
		proj = 0.;

	dRed *= _dDiffuseRed * proj;
	dGreen *= _dDiffuseGreen * proj;
	dBlue *= _dDiffuseBlue * proj;
}
////////////////////////////////////////////////////////////////////////////////
