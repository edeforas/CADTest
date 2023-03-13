#ifndef NurbsRevolve_
#define NurbsRevolve_

#include "Geometry.h"

class NurbsCurve; 
class NurbsSurface;

///////////////////////////////////////////////////////////////////////////
class NurbsRevolve
{
public:
	NurbsRevolve();
	virtual ~NurbsRevolve();
	bool revolve(const NurbsCurve& nc, NurbsSurface& ns) const;
};
///////////////////////////////////////////////////////////////////////////

#endif